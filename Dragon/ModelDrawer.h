#pragma once

#include <map>

#include "Drawer.h"
#include "Model.h"
#include "Transform.h"
#include "CommonType.h"

using std::map;


/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������ModelDrawer
*	�衡�������̳���Drawer�������ھ�̬ģ�͵���Ⱦ��
*
*/
class ModelDrawer : public Drawer
{
private:
	StaticModel *m_mesh;
	Transform *m_transform;

	static map<StaticModel*, GraphicsBuffer*> m_buffersMap;

protected:
	ModelDrawer(Model *mesh, Transform *transform, string shaderName = "AssimpModel") : Drawer(shaderName)
	{
		m_mesh = dynamic_cast<StaticModel*>(mesh);
		m_transform = transform;
		m_buffers = LoadGraphicsBuffer(m_mesh);
	}

public:
	virtual void Draw();
	virtual void PublicSet();
	virtual RenderLevel GetRenderLevel(void) { return RenderLevel::Entity; }

	static ModelDrawer* Create(Model *mesh, Transform *transform);
	static GraphicsBuffer* LoadGraphicsBuffer(StaticModel *mesh);		//�����ظ�����ͬModel���ٻ������
};