#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
class GoalObject : public AbstractComponent {
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	void Initialize(float Zpos, GameObject* player);
private:
	GameObject* goalObj = nullptr;
	GameObject* pPlayer = nullptr;
	
};