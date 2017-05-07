#include "AnimationModelDrawer.h"
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <GLM\gtx\euler_angles.hpp>
#include "Shader.h"
#include "Camera.h"
#include "ResourceSystem.h"
#include "Model.h"

void AnimationModelDrawer::PublicSet()
{
	Camera *camera = ResourceSystem::GetMainCamera();
	mat4 view = camera->GenViewMatrix();
	mat4 projection = camera->GenProjectionMatrix();
	vec3 viewerPosition = camera->GetViewPosition();
	Light *light = ResourceSystem::GetLight();
	vec3 lightColor = light->GetLightColor();
	vec3 lightPosition = light->GetTransform()->getPosition();

	glUniform3fv(m_shader->GetUniformLocation("viewerPosition"), 1, value_ptr(viewerPosition));
	glUniform3fv(m_shader->GetUniformLocation("lightColor"), 1, value_ptr(lightColor));
	glUniform3fv(m_shader->GetUniformLocation("lightPosition"), 1, value_ptr(lightPosition));
	glUniform1f(m_shader->GetUniformLocation("material.shininess"), 32.0f);
	m_shader->SetUniformValue("view", view);
	m_shader->SetUniformValue("projection", projection);
}

AnimationModelDrawer * AnimationModelDrawer::Create(Model * model, Transform * transform)
{
	AnimationModelDrawer *drawer = new AnimationModelDrawer(model, transform);
	drawer->Register();
	return drawer;
}

GraphicsBuffer * AnimationModelDrawer::LoadGraphicsBuffer(SkeletonModel * model)
{
	if (m_buffersMap.find(model) != m_buffersMap.end())
		return m_buffersMap[model];

	//�����µ�Mesh������
	//ֻ��VAO��VBO
	GraphicsBuffer *buffer = new GraphicsBuffer();
	int meshCount = model->GetMeshCount();
	buffer->m_vbo.resize(meshCount);
	buffer->m_vao.resize(meshCount);

	glGenBuffers(meshCount, buffer->m_vbo.data());
	glGenVertexArrays(meshCount, buffer->m_vao.data());
	m_buffersMap[model] = buffer;

	//������������
	for (int i = 0; i < meshCount; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer->m_vbo[i]);

		//���ݴ���
		const SkeletonMesh* mesh = model->GetMesh(i);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SkeletonVertex) * mesh->GetVertexCount(), mesh->GetVertex(), GL_STATIC_DRAW);

		glBindVertexArray(buffer->m_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, buffer->m_vbo[i]);

		//��������ָ��
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SkeletonVertex), (GLvoid*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SkeletonVertex), (GLvoid*)offsetof(SkeletonVertex, m_normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SkeletonVertex), (GLvoid*)offsetof(SkeletonVertex, m_texCoord));

		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, 4, GL_INT, sizeof(SkeletonVertex), (GLvoid*)offsetof(SkeletonVertex, m_weight.m_boneIndex));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(SkeletonVertex), (GLvoid*)offsetof(SkeletonVertex, m_weight.m_weight));

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return buffer;
}

AnimationModelDrawer::AnimationModelDrawer(Model * model, Transform * transform, string shaderName) : Drawer(shaderName)
{
	m_model = dynamic_cast<SkeletonModel*>(model);
	m_transform = transform;
	m_buffers = LoadGraphicsBuffer(m_model);
	m_boneTransform = nullptr;
}

void AnimationModelDrawer::Draw()
{
	//Model����
	mat4 model;
	model = translate(model, m_transform->getPosition());
	vec3 rotation = m_transform->getRotation();
	model = model * (mat4)eulerAngleXYZ(radians((double)rotation.x), radians((double)rotation.y), radians((double)rotation.z));
	model = scale(model, m_transform->getScale());

	GLenum modelLocation = m_shader->GetUniformLocation("model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	m_shader->SetUniformValue("bones", *m_boneTransform);

	int subMeshCount = m_model->GetMeshCount();
	const SkeletonMesh *mesh = m_model->GetMesh(0);
	int specularIndex = 0;
	int diffuseIndex = 0;
	stringstream ss;
	for (int i = 0; i < subMeshCount; i++)
	{
		const SkeletonMesh *mesh = m_model->GetMesh(i);
		for (int j = 0; j < mesh->GetTextureCount(); j++)
		{
			const Texture *texture = mesh->GetTexture(j);
			ss.clear();
			glActiveTexture(GL_TEXTURE0 + j);
			string texName = texture->m_type;
			if (texName == "texSpecular")
				ss << specularIndex++;
			else if (texName == "texDiffuse")
				ss << diffuseIndex++;
			string str;
			ss >> str;
			texName = "material." + texName + str;
			GLenum location = glGetUniformLocation(m_shader->GetShaderID(), texName.c_str());
			glUniform1i(location, GL_TEXTURE0 + j);
			glBindTexture(GL_TEXTURE_2D, texture->m_id);
		}

		glBindVertexArray(m_buffers->m_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
		glBindVertexArray(0);

		for (GLuint i = 0; i < mesh->GetTextureCount(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glActiveTexture(GL_TEXTURE0);
	}
}

map<SkeletonModel*, GraphicsBuffer*> AnimationModelDrawer::m_buffersMap;