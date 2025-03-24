/**
 * @file   Enemy.cpp
 *
 * @brief  �G�l�~�[�I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/23
 */

#include "pch.h"
#include "Enemy.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

// �g�p����}�l�[�W���[
#include "../Managers/ObjectManager.h"

// �֘A�̂���I�u�W�F�N�g
#include "Player.h"

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
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
	// �x�����p
	elapsedTime;

	// �v���C���[�̍U���ɑ΂��鏈��
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	if (pPlayer->IsAttack())
	{
		// �v���C���[�̍U���������������ǂ���
		ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));
		ColliderBace* pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("DamageCollider"));

		if (pCollider->IsHit(pPlayerCollider))
		{
			// �G�l�~�[�̍폜
			mp_ObjectManager->DeleteObject(this);
		}
	}
}
