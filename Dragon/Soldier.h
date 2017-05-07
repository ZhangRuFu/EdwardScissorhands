#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "ModelDrawer.h"
#include "RenderSystem.h"

/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������Soldier
*	�衡��������Ϸ�߼���ʿ����
*
*/
class Soldier : public GameSpirit
{
private:
	Model *m_mesh;
	ModelDrawer *m_drawer;

public:
	Soldier(void)
	{
		m_mesh = MeshManager::LoadModel("E:\\GameDevelop\\Model\\nanosuit\\nanosuit.obj");
		m_drawer = ModelDrawer::Create(m_mesh, &m_transform);
	}

	void Move()
	{

	}
};