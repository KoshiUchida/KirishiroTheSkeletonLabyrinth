/**
 * @file   Floor.cpp
 *
 * @brief  ���I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "Floor.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"


/// <summary>
/// Costructor
/// </summary>
Floor::Floor(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);

	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Floor.sdkmesh"));
}

/// <summary>
/// Destructor
/// </summary>
Floor::~Floor() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void Floor::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Floor::Process(float elapsedTime)
{
	// �x�����p
	elapsedTime;
}

