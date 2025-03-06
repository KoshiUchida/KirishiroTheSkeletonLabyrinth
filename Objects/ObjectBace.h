/**
 * @file   ObjectBace.h
 *
 * @brief  �I�u�W�F�N�g���N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once
#include <memory>

#include "Transform.h"

class ObjectManager;
class SceneBace;

/// <summary>
/// �I�u�W�F�N�g�̊��N���X
/// </summary>
class ObjectBace
{
protected:
	// �I�u�W�F�N�g�}�l�[�W���ւ̃|�C���^
	ObjectManager* mp_ObjectManager;

	// �V�[���ւ̃|�C���^
	SceneBace* mp_Scene;

	// �g�����X�t�H�[��
	std::unique_ptr<Transform> m_Transform;

public:
	// Constructor & Destructor
	ObjectBace(SceneBace* pScene) noexcept;
	virtual ~ObjectBace() noexcept;

	// Main System
	virtual void Initialize(                 ) = 0;
	virtual void Update    (float elapsedTime) = 0;

	// Getter
	Transform* GetTransformPointer() { return m_Transform.get(); }
};

