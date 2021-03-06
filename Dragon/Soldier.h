#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "ModelDrawer.h"
#include "RenderSystem.h"

/*
*	引擎版本：Dragon Engine v0.1;
*	类　　名：Soldier
*	描　　述：游戏逻辑：士兵类
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