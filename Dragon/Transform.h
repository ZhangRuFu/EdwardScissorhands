#pragma once
#include <GLM\glm.hpp>
/*
 *	����汾��Dragon Engine v0.1;
 *	�ࡡ������Transform
 *	�衡������GameEntity�Ļ��������������Ϸ�����λ�úͷ���
 *
 */
using namespace glm;
class Transform
{
	friend class GameEntity;
private:
	vec3 m_position;		//λ��
	vec3 m_rotation;		//��ת
	vec3 m_scale;			//����
	vec3 m_orientation;		//����

public:
	Transform(vec3 position = vec3(0, 0, 0), vec3 rotation = vec3(0, 0, 0) , vec3 scale = vec3(1, 1, 1));

public:
	void Move(float speed = 5);
	void Move(vec3 step);
	void ChangeOrientation(float angle);		//��ʱֻ����XZƽ����Y����ת
	void Scale(vec3 &scale);
	
	vec3 getPosition(void);
	vec3 getRotation(void);
	vec3 getScale(void);
	vec3 getOrientation(void);
};