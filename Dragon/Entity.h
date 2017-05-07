#pragma once
#include "Transform.h"
/*
*	����汾��	Dragon Engine v0.1;
*	�ࡡ������	GameEntity
*	�衡������	������Ϸ�еĻ������󣬿�����һ����ҿ��ƵĽ�ɫ�������е����Ӻ�������Ч����ȵ�
				����Dragon��֪������ڵ�����
*
*/
class GameEntity
{
protected:
	Transform m_transform;			//��ά�ռ�Ļ�����Ϣ

public:
	GameEntity();
	GameEntity(Transform &transform);
	Transform *GetTransform(void);
};

/*
*	����汾��	Dragon Engine v0.1;
*	�ࡡ������	GameSpirit
*	�衡������	������Ϸ�еľ��ж�̬���ԣ���Ҫ����Move()�������Ļ�������,Dragon������Ϸ����ʱ������GameSpirit����Move
*
*/

class GameSpirit : public GameEntity
{

public:
	GameSpirit();
	GameSpirit(Transform &transform);

public:
	virtual void Move() = 0;
};

