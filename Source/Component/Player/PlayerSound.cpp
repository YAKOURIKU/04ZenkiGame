#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::onUpdate()
{
	if (GameInput::getInstance().getPlayerDash())
	{
		dash();
	}
	if (GameInput::getInstance().getSliding())
	{
		sliding();
	}

}

void PlayerSound::play(const std::string& audioName, int loopCount, float volume)
{
	//Sound名設定
	pAudio->setAudio(audioName);
	//音の大きさ設置
	pAudio->setVolume(volume);
	//規定回数まで再生
	pAudio->play(loopCount);
}

void PlayerSound::dash()
{
	if(!pAudio->isPlaying())play("Dash",0,0.1f);
}

void PlayerSound::sliding()
{
	play("Sliding", 0, 0.1f);
}
