#pragma once
#include "Component/Base/AbstractComponent.h"

class TestUI;
class Option;
class CollectItemUI;
class TimeLimitDraw;

//プレイヤーのパラメータ管理
class PlayerParamManager
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	//燃料がゼロかどうか
	bool isFuelZero() const;

	//加速度を取得
	float getAcceleration() const;

	void onDamage();

private:
	TestUI* m_pTestUI;
	Option* m_Option;
	CollectItemUI* m_Item;
	TimeLimitDraw* m_TimeLimit;

	//体力
	float m_Health = 5.0f;
	//加速度を取得
	float m_Acceleration;
	//燃料
	float m_Fuel = 5.0f;
};