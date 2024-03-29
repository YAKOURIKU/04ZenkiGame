#include "CheckPoint.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/TestUI/TimeLimitUi.h"

void CheckPoint::onStart()
{
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	collider->setUseGravity(false);
	collider->setMass(0.0f);

	// 敵としてタグ付け
	getUser().setTag("Gimmick");

	isDead = false;

	GameObj = new GameObject(getUser().getGameMediator());

	// 実体をなくす
	getUser().getComponent<BoxColiiderBt>()->setTrigger(true);
}

void CheckPoint::onUpdate()
{
	if (IsDead())
	{
		getUser().destroy();
	}
}

void CheckPoint::onTriggerEnter(GameObject* pHit)
{
	TimeLimitUi::AddLimit(3);

	//敵でないならreturn
	if (!pHit->compareTag("Gimmick"))
		return;

	SetDead(true);
}
