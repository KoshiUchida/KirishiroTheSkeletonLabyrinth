/**
 * @file   ObjectManager.h
 *
 * @brief  �I�u�W�F�N�g�Ǘ��N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "../Objects/ObjectBace.h"

/// <summary>
/// �I�u�W�F�N�g�Ǘ��N���X
/// </summary>
class ObjectManager
{
private:
	// �G�C���A�X�錾
	using ObjectCollection
		= std::unordered_map<std::string, std::unique_ptr<ObjectBace>>;

	// �I�u�W�F�N�g�̏W��
	ObjectCollection m_Objects;

public:
	// Main System
	ObjectManager() noexcept;
	~ObjectManager() noexcept;
	void Update(float elapsedTime);
	void Finalize();

	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	ObjectBace* GetObjectPtr(const std::string& objectName);
};

