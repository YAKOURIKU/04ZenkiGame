#include "StageLoader.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"
#include "Utility/CoordConverter.h"

StageLoader::StageLoader(IGameMediator* pGameMediator)
	: m_pGameMediator(pGameMediator)
{
}

void StageLoader::loadStage(const StageInfo& stageInfo)
{
	createStageBase(stageInfo);
	createObjects(stageInfo);
}

void StageLoader::createStageBase(const StageInfo& stageInfo)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//�ʂ̐�
	const int faceCount = 36;
	//�p�x
	const float rad = DirectX::XM_2PI / faceCount;
	//�~���̔��a
	const float radius = stageInfo.m_Radius - 1.0f;

	//�~���𐶐�
	for (int i = 0; i < faceCount; i++)
	{
		Vec3 cylinder(radius, rad * i, stageInfo.m_Length);

		//�Q�[���I�u�W�F�N�g����
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));

		//���W�ݒ�
		pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
		//�T�C�Y�ݒ�
		pFloor->getTransform().setLocalScale(Vec3(1.0f, radius * 0.25f, 200.0f));
		//��]�ݒ�
		pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i));
	}
}

void StageLoader::createObjects(const StageInfo& stageInfo)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//�I�u�W�F�N�g�z�u���𑖍�
	for (auto& objectPlaceInfo : stageInfo.m_ObjectPlaceInfoList)
	{
		//�I�u�W�F�N�g����
		auto pObject = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
		pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);

		//�R���C�_�[�ǉ�
		auto pCollider = pObject->addComponent<BoxColiiderBt>();

		if (objectPlaceInfo.m_ObjectName == "Wall")
		{
			//�X�P�[���ݒ�
			pObject->getTransform().setLocalScale(Vec3(3.0f, stageInfo.m_Radius * 0.3f, 1.0f));
			//�p�x�ݒ�
			pObject->getTransform().setLocalAngleZ(objectPlaceInfo.m_Angle);
			//�F�ݒ�
			pObject->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::LawnGreen, 1.0f));

			pCollider->setMass(0.0f);
			pCollider->setUseGravity(false);
			pCollider->setTrigger(false);
		}

		if (objectPlaceInfo.m_ObjectName == "TestEnemy")
		{
			//�G�p�R���|�[�l���g�ǉ�
			auto pTestEnemy = pObject->addComponent<TestEnemy>();
			pTestEnemy->init(-10.0f, 0.0f, stageInfo.m_Radius);

			pCollider->setMass(1.0f);
			pCollider->setUseGravity(false);
			pCollider->setTrigger(true);
			pCollider->applyForceImpluse(Vec3(0.0f, 0.0f, -1.0f));
		}
	}
}