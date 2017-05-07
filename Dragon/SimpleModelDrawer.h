#pragma once
/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������SimpleModelDrawer
*	�衡�������̳���Drawer�������ڼ򵥴�ɫģ�͵���Ⱦ��
*
*/
#include <map>
#include "Drawer.h"
#include "Model.h"
#include "Transform.h"
#include "CommonType.h"
using std::map;

class SimpleModelDrawer : public Drawer
{
private:
	StaticModel *m_mesh;
	Transform *m_transform;
	vec3 m_color;

private:
	static map<StaticModel*, GraphicsBuffer*> m_buffersMap;

protected:
	SimpleModelDrawer(Model *mesh, Transform *transform, vec3 color, string shaderName = "SimpleModel") : Drawer(shaderName)
	{
		m_mesh = dynamic_cast<StaticModel*>(mesh);
		m_transform = transform;
		m_color = color;
		m_buffers = LoadGraphicsBuffer(m_mesh);
	}

public:
	virtual void Draw();
	virtual void PublicSet();
	virtual RenderLevel GetRenderLevel(void) { return RenderLevel::Entity; }

	static SimpleModelDrawer* Create(Model *mesh, Transform *transform, vec3 color);
	static GraphicsBuffer* LoadGraphicsBuffer(StaticModel *mesh);
};