#pragma once
/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������Mesh
*	�衡����������һ��GameEntity����ۡ����ӻ�
*
*/

#include <vector>
#include <map>
#include <GLM\glm.hpp>
#include "Mesh.h"
#include "CommonType.h"

using std::vector;
using std::map;
using glm::mat4;

/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������Model
*	�衡������ģ����ĳ������
*
*/

class Model
{
public:
	virtual bool hasAnimation() = 0;

	virtual void AddTexture(string texturePath) = 0;
};



/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������StaticModel
*	�衡��������̬ģ��
*
*/
class StaticModel : public Model
{
private:
	vector<StaticMesh*> m_subMeshes;
	vector<Texture*> m_texutres;

public:
	StaticModel(vector<StaticMesh*> subMeshes, vector<Texture*> textures);

	virtual bool hasAnimation() { return false; }

	int GetSubMeshCount();

	const StaticMesh* GetMesh(int index);

	void AddTexture(string texturePath);
};

/*
*	����汾��Dragon Engine v0.1;
*	�ࡡ������SkeletonMesh
*	�衡��������̬ģ�͵�������
*
*/
struct Key
{
	int m_key;
	float m_value;

public:
	Key(int key, float value) :m_key(key), m_value(value) {}
};

class BoneAnimation
{
private:
	vector<Key>* m_translation[3];			//Translate��X��Y��Z������Key
	vector<Key>* m_rotate[3];				//Rotate��X��Y��Z������Key
	vector<Key>* m_scale[3];				//Scale��X��Y��Z������Key
	vec3* m_prePostRotate;

public:
	enum FrameType { TX, TY, TZ, RX, RY, RZ, SX, SY, SZ };

public:
	BoneAnimation()
	{
		for (int i = 0; i < 3; i++)
		{
			m_translation[i] = nullptr;
			m_rotate[i] = nullptr;
			m_scale[i] = nullptr;
			m_prePostRotate = nullptr;
		}
	}
	int GetKeyCount(FrameType type)
	{
		switch (type)
		{
		case FrameType::TX:
		case FrameType::TY:
		case FrameType::TZ:
			m_translation[type]->size();
			break;
		case FrameType::RX:
		case FrameType::RY:
		case FrameType::RZ:
			m_rotate[type % 3]->size();
			break;
		case FrameType::SX:
		case FrameType::SY:
		case FrameType::SZ:
			m_scale[type % 3]->size();
			break;
		}
	}

	void AddFrame(vector<Key>* values, FrameType type)
	{
		switch (type)
		{
		case FrameType::TX:
		case FrameType::TY:
		case FrameType::TZ:
			m_translation[type] = values;
			break;
		case FrameType::RX:
		case FrameType::RY:
		case FrameType::RZ:
			m_rotate[type % 3] = values;
			break;
		case FrameType::SX:
		case FrameType::SY:
		case FrameType::SZ:
			m_scale[type % 3] = values;
			break;
		}
	}
	void AddFrame(vec3 *prePostRotate)
	{
		m_prePostRotate = prePostRotate;
	}

	mat4 GetTransform(float key);
	vec3 GetKeyValue(float key, vector<Key>* Keyvector[3]);
};

//������Ϣ
struct Bone
{
	string m_name;
	mat4 m_offsetMatrix;
	int m_childCount;
	Bone *m_child;
	BoneAnimation *m_animation;

	Bone(void) : m_child(nullptr), m_animation(nullptr) {}
};

//�ɹ�������ù�����������������
struct BoneIndex
{
	Bone *bone;
	int index;
};



class BoneManager
{
public:
	BoneManager(Bone *rootBone);
	const BoneIndex* GetBoneIndex(string boneName);
	void UpdateSkeleton(float key, vector<mat4> &transform);
	void UpdateSkeleton(Bone *bone, mat4 &parentTransform, float key, vector<mat4> &transform);
	bool isRootBone(Bone *bone) { return bone == m_rootBone; }
	int GetBoneCount(void) { return m_bonesMap.size(); }

private:
	Bone *m_rootBone;
	map<string, BoneIndex> m_bonesMap;		//������-����ӳ���
};



class SkeletonModel : public Model
{
	friend class FBXModelLoader;
private:
	vector<SkeletonMesh> m_meshes;			//SkeletonSubMesh
	vector<Texture*> m_texutres;			//Texture
	
	BoneManager *m_boneManager;				//Bone
	
	int m_keyCount;							//����֡����

public:
	class SkeletonModelException
	{
	private:
		string m_err;

	public:
		SkeletonModelException(string err) :m_err(err) {}
	};

public:
	SkeletonModel(void);

	virtual bool hasAnimation(void) { return true; }
	virtual void AddTexture(string texturePath) {};

	int GetMeshCount() { return m_meshes.size(); };
	int GetAnimationKeyCount() { return m_keyCount; }
	BoneManager* GetBoneManager() { return m_boneManager; }
	const SkeletonMesh* GetMesh(int index) { return &m_meshes[index]; };
};
