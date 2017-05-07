#pragma once
#include "Entity.h"
#include "Model.h"
#include "AnimationModelDrawer.h"
#include "RenderSystem.h"
#include "MeshManager.h"
#include "AnimationController.h"

/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������Monster
*	�衡��������Ϸ�߼���������
*
*/
class Monster : public GameSpirit
{
private:
	SkeletonModel *m_model;
	AnimationModelDrawer *m_drawer;
	AnimationController *m_animationController;

public:
	Monster(void)
	{
		m_model = dynamic_cast<SkeletonModel*>(MeshManager::LoadModel("E:\\GameDevelop\\Model\\Monster_Animation\\monster.FBX"));
		m_drawer = AnimationModelDrawer::Create(m_model, &m_transform);
		m_animationController = new AnimationController(m_drawer, m_model);
	}

	void Move()
	{

	}
};