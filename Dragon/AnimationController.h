#pragma once
#include "Model.h"
#include "AnimationModelDrawer.h"
#include "AnimationClipManager.h"

class AnimationController
{
	//����״̬����Ϣ
	SkeletonModel *m_model;
	AnimationModelDrawer *m_drawer;
	AnimationClipManager *m_clipManager;	//Ƭ�ι�����
	AnimationClip *m_currentClip;			//��ǰ����Ƭ��
	BoneManager *m_boneManager;				//������
	vector<mat4> m_boneTransform;

	float m_spf;							//ÿ֡����ʱ��
	float m_curTime;						//��ǰ֡����ʱ��
	int m_keyCount;							//����֡����
	float m_curKey;							//��ǰ֡
	bool m_isPlay;							//�Ƿ񲥷�

public:
	AnimationController(AnimationModelDrawer *drawer, SkeletonModel *model);
	void Pause(void) { m_isPlay = false; }
	void Play(void) { m_isPlay = true; }
	void Move(void);
};