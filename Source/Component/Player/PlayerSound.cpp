#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::play(std::string& audioName, int loopCount, float volume)
{
	//Sound名設定
	pAudio->setAudio(audioName);
	//音の大きさ設置
	pAudio->setVolume(volume);
	//規定回数まで再生
	pAudio->play(loopCount);
}
