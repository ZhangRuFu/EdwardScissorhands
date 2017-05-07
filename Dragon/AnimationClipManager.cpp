#include "AnimationClipManager.h"

void AnimationClipManager::ExportXML(string path)
{
	//����Ƭ�����ݵ�XML�ļ�
}

void AnimationClipManager::ImportXML(string path)
{
	//��XML�ļ�����Ƭ������
}

AnimationClip * AnimationClipManager::GetAnimationClip(string clipName)
{
	for (vector<AnimationClip*>::const_iterator i = m_clips.cbegin(); i != m_clips.cend(); i++)
		if ((*i)->m_clipName == clipName)
			return (*i);
	return nullptr;
}
