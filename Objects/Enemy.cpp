/**
 * @file   Enemy.cpp
 *
 * @brief  �G�l�~�[�I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/20
 */

#include "pch.h"
#include "Enemy.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ���W�̐ݒ�
	pTransform->SetPosition(position);

	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, DirectX::SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));
}

/// <summary>
/// Destructor
/// </summary>
Enemy::~Enemy() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::Process(float elapsedTime)
{
	elapsedTime;
}
