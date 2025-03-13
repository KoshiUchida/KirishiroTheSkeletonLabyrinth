/**
 * @file   ObjectManager.cpp
 *
 * @brief  �I�u�W�F�N�g�Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "ObjectManager.h"
#include "../Components/ComponentsBace.h"
#include "../Components/RendererBace.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectManager::ObjectManager() noexcept = default;

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectManager::~ObjectManager() noexcept
{
	Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ObjectManager::Update(float elapsedTime)
{
	// �I�u�W�F�N�g�̍X�V����
	for (auto& element : m_Objects)
		element.second->Update(elapsedTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void ObjectManager::Render(const DirectX::SimpleMath::Matrix& view)
{
	// �I�u�W�F�N�g�̕`�揈��
	for (auto& element : m_Objects)
		element.second->Render(view);
}

/// <summary>
/// �I������
/// </summary>
void ObjectManager::Finalize()
{
	for (auto& element : m_Objects)
		element.second.reset();

	m_Objects.clear();
}

/// <summary>
/// �I�u�W�F�N�g�̒ǉ�
/// </summary>
/// <param name="objectName">�ǉ�����I�u�W�F�N�g��</param>
/// <param name="object">�ǉ�����I�u�W�F�N�g�f�[�^</param>
void ObjectManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	// �V�K�I�u�W�F�N�g�̏���������
	object->Initialize();

	// �I�u�W�F�N�g�̓o�^
	m_Objects.emplace(objectName, std::move(object));
}

ObjectBace* ObjectManager::GetObjectPtr(const std::string& objectName)
{
	if (m_Objects.count(objectName) == 0)
	{
		return nullptr;
	}

	return m_Objects.at(objectName).get();
}
