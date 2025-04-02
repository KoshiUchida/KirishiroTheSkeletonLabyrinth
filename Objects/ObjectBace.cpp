/**
 * @file   ObjectBace.cpp
 *
 * @brief  �I�u�W�F�N�g���N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"
#include "../Managers/SceneManager.h" 
#include "../Components/ComponentsBace.h"
#include "../Components/RendererBace.h"
#include "../Components/SphereCollider.h"
#include "../Components/Renderer3DWithAnimation.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene, const std::string& name) noexcept :
	mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() },
	mp_Scene        { pScene },
	m_Name          { name },
	m_Layer         { 0 }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_ObjectManager = nullptr;
	mp_Scene = nullptr;


	for (auto& element : m_Components)
		element.second.reset();

	m_Components.clear();
}

/// <summary>
/// �I�u�W�F�N�g�S�̂̍X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ObjectBace::Update(float elapsedTime)
{
	Process(elapsedTime);

	for (auto& component : m_Components)
	{
		if (component.second->GetTag() == ComponentsBace::Tags::Update)
		{
			// TODO::�^�O�uUpdate�v�̃R���|�[�l���g���쐬������C������
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::UAndR)
		{
			static_cast<Renderer3DWithAnimation*>(component.second.get())->Update(elapsedTime);
		}
		else
			component;
	}
}

/// <summary>
/// �I�u�W�F�N�g�S�̂̕`�揈��
/// </summary>
void ObjectBace::Render(const DirectX::SimpleMath::Matrix& view)
{
	for (auto& component : m_Components)
	{
		if (component.second->GetTag() == ComponentsBace::Tags::Render)
		{
			static_cast<RendererBace*>(component.second.get())->Draw(view);
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::Collider)
		{
			SphereCollider* sphere = static_cast<SphereCollider*>(component.second.get());
			if (sphere)
				sphere->Render(view);
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::UAndR)
		{
			static_cast<Renderer3DWithAnimation*>(component.second.get())->Draw(view);
		}
		else
			component;
	}
}

/// <summary>
/// �R���|�[�l���g�̒ǉ�
/// </summary>
/// <param name="component">�ǉ�����R���|�[�l���g</param>
void ObjectBace::AddComponent(std::unique_ptr<ComponentsBace> component)
{
	std::string AddName{ component->GetName() };

	m_Components.emplace(AddName, std::move(component));
}

/// <summary>
/// ���C���[�̐ݒ�֐�
/// </summary>
void ObjectBace::SetLayer(int layer)
{
	m_Layer = layer;
}

/// <summary>
/// �R���|�[�l���g�ւ̃|�C���^�̎擾
/// </summary>
/// <returns>�R���|�[�l���g�ւ̃|�C���^�܂���NULL</returns>
ComponentsBace* ObjectBace::GetComponentPtr(const std::string& name)
{
	if (m_Components.count(name) == 0)
	{
		return nullptr;
	}

	return m_Components.at(name).get();
}

ObjectBace* ObjectBace::GetObjectPtr(const std::string& name)
{
	return mp_ObjectManager->GetObjectPtr(name);
}

/// <summary>
/// ���O�̎擾�֐�
/// </summary>
/// <returns>���̃I�u�W�F�N�g�̖��O</returns>
std::string ObjectBace::GetName() const noexcept
{
	return m_Name;
}

/// <summary>
/// ���C���[�̎擾�֐�
/// </summary>
int ObjectBace::GetLayer() const noexcept
{
	return m_Layer;
}

