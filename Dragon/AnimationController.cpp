#include "AnimationController.h"
#include "ResourceSystem.h"
#include "Time.h"

AnimationController::AnimationController(AnimationModelDrawer * drawer, SkeletonModel * model)
{
	Init(drawer, model);
}

AnimationController::AnimationController(AnimationModelDrawer * drawer, SkeletonModel * model, string controllerName)
{
	Init(drawer, model);
	m_controllerMap[controllerName] = this;
}

void AnimationController::Move(void)
{
	//ÿ֡���������Transform������Drawer
	if (!m_isPlay)
		return;
	m_curTime += Time::GetDeltaTime();
	if (m_curTime < m_spf)
		return;
	m_curTime = 0;
	m_curKey++;
	if (m_curKey > m_keyCount)
		m_curKey -= m_keyCount;

	m_boneManager->UpdateSkeleton(m_curKey, m_boneTransform);
}

AnimationController * AnimationController::GetController(string controllerName)
{
	if (m_controllerMap.find(controllerName) != m_controllerMap.end())
		return m_controllerMap[controllerName];
}

void AnimationController::Init(AnimationModelDrawer * drawer, SkeletonModel * model)
{
	m_drawer = drawer;
	m_model = model;
	m_spf = 1.0 / 30 * 1000;		//ms
	m_curTime = 0;
	m_boneManager = m_model->GetBoneManager();
	m_boneTransform.resize(m_boneManager->GetBoneCount());
	m_drawer->UpdateBoneTransform(&m_boneTransform);
	m_curKey = 0;
	m_keyCount = model->GetAnimationKeyCount();
	m_isPlay = false;
	ResourceSystem::Register(this);
}

map<string, AnimationController*> AnimationController::m_controllerMap;