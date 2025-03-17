/**
 * @file   Cylinder.h
 *
 * @brief  �~���I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/18
 */

#include "pch.h"
#include "Cylinder.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"

/// <summary>
/// Constructor
/// </summary>
Cylinder::Cylinder(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetPosition(position);
	pTransform->SetScaleY(1.1f);

	AddComponent(std::make_unique<Renderer3D>(mp_Scene, pTransform, L"Resources\\Models\\Clinder.sdkmesh"));
}

/// <summary>
/// Destructor
/// </summary>
Cylinder::~Cylinder() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void Cylinder::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Cylinder::Process(float elapsedTime)
{
	// �x�����p
	elapsedTime;
}
