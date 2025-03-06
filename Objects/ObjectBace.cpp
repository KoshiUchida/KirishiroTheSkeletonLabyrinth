/**
 * @file   ObjectBace.cpp
 *
 * @brief  �I�u�W�F�N�g���N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"
#include "../Managers/SceneManager.h" 
#include "../Components/ComponentsBace.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() }
	, mp_Scene        { pScene }
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
/// �R���|�[�l���g�̒ǉ�
/// </summary>
/// <param name="component">�ǉ�����R���|�[�l���g</param>
void ObjectBace::AddComponent(std::unique_ptr<ComponentsBace> component)
{
	std::string AddName{ component->GetName() };

	m_Components.emplace(AddName, std::move(component));
}

/// <summary>
/// �R���|�[�l���g�ւ̃|�C���^�̎擾
/// </summary>
/// <returns>�R���|�[�l���g�ւ̃|�C���^�܂���NULL</returns>
ComponentsBace* ObjectBace::GetComponentPtr(const std::string& tag)
{
	if (m_Components.count(tag) == 0)
	{
		return nullptr;
	}

	return m_Components.at(tag).get();
}

std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>* ObjectBace::GetComponentsPtr()
{
	return &m_Components;
}

