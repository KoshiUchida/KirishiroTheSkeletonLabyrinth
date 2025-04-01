/**
 * @file   Enemy.cpp
 *
 * @brief  �G�l�~�[�I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "Enemy.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"
#include "../Components/SphereCollider.h"

// �g�p����}�l�[�W���[
#include "../Managers/ObjectManager.h"

// �֘A�̂���I�u�W�F�N�g
#include "Player.h"

using namespace std;
using namespace DirectX;

// ��]�̐ݒ�l
static constexpr float RotateSpeedSpeed{ XM_PI / 36.f };
static constexpr float RotateSpeedA{ XM_PI / 48.f };
static constexpr float RotateSpeedFC{ 0.95f };

// ��]��~�͈̔�
static constexpr float RotateRange{ XM_PI / 36.f };

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const string& name, const SimpleMath::Vector3& position) noexcept :
	ObjectBace(pScene, name),
	m_Action{ CurrentCourseOfAction::NONE },
	m_SpownPosition{ position },
	m_PlayerFound{ false },
	m_RotateSpeed{ RotateSpeedSpeed, RotateSpeedA, RotateSpeedFC },
	m_RotatePlusMinus{ 0.f },
	m_CanAttackPlayer{ false }
{
	AddComponent(make_unique<Transform>());

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ���W�̐ݒ�
	pTransform->SetPosition(m_SpownPosition);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.2f, 0.1f, 0.2f)));
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	static constexpr float OffsetDamageCollider{ 0.7f };
	pDamageCollider->SetOffset(SimpleMath::Vector3(OffsetDamageCollider, 0.f, 0.f));

	static constexpr float PerceptionRange    { 7.f };
	static constexpr bool  ShowPerceptionRange{ true };

	AddComponent(make_unique<SphereCollider>(pScene, "PerceptionRange", pTransform,PerceptionRange, ShowPerceptionRange));
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
	Move(elapsedTime);

	Collision();
}

/// <summary>
/// �ړ��֌W����
/// </summary>
void Enemy::Move(float elapsedTime)
{
	switch (m_Action)
	{
	case Enemy::CurrentCourseOfAction::NONE:
		{
			// �v���C���[��m�o�����ꍇCHASE��
			if (m_PlayerFound)
				m_Action = CurrentCourseOfAction::CHASE;
			return;
		}
	case Enemy::CurrentCourseOfAction::CHASE:
		{
			// �v���C���[�̃g�����X�t�H�[�����擾
			Transform* pPlayerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

			// ���g�̍��W���擾
			Transform* thisTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

			// �v���C���[�̂���������擾
			float playerDirection = XM_PI / -2.f + atan2f((pPlayerTransform->GetPositionX() - thisTransform->GetPositionX()), (pPlayerTransform->GetPositionZ() - thisTransform->GetPositionZ()));

			// ���݂̕�������̍����ʏ���
			if (thisTransform->GetRotateY() >= playerDirection - RotateRange / 2.f && thisTransform->GetRotateY() <= playerDirection + RotateRange / 2.f)
			{
				m_RotateSpeed.Stop(elapsedTime);
			}
			else
			{
				m_RotateSpeed.Up(elapsedTime);

				if (thisTransform->GetRotateY() < playerDirection - RotateRange / 2.f)
				{
					m_RotatePlusMinus = 1.f;
				}
				else if (thisTransform->GetRotateY() > playerDirection + RotateRange / 2.f)
				{
					m_RotatePlusMinus = -1.f;
				}
			}

			// ���g�̉�]
			if (m_RotateSpeed.Get() != 0.f && m_RotatePlusMinus != 0.f)
				thisTransform->AddRotateY(m_RotateSpeed.Get() * m_RotatePlusMinus);

			// �v���C���[���m�o�O�ɂ���ꍇNONE��
			if (m_PlayerFound)
				m_Action = CurrentCourseOfAction::NONE;
			return;
		}
	default:
		// ERORR : ���肦�Ȃ����� m_Action�̒l���m�F���Ă��������B
		return;
	}
}

/// <summary>
/// �R���C�_�[�֌W����
/// </summary>
void Enemy::Collision()
{
	// ���g�̃R���C�_�[���擾
	ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));

	// �v���C���[�̎擾
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	// �v���C���[�̃R���C�_�[�ւ̃|�C���^
	ColliderBace* pPlayerCollider;

	// �v���C���[�̍U���ɑ΂��鏈��
	if (pPlayer->IsAttack())
	{
		// �v���C���[�̍U���������������ǂ���
		pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("DamageCollider"));

		if (pCollider->IsHit(pPlayerCollider))
			// �G�l�~�[�̍폜
			mp_ObjectManager->DeleteObject(this);
	}

	// �����o������
	pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("Collider"));
	pPlayerCollider->Collision(pCollider);

	// �v���C���[���m�o�͈͂ɂ��邩
	m_PlayerFound = static_cast<ColliderBace*>(GetComponentPtr("PerceptionRange"))->IsHit(pPlayerCollider->GetPosition());

	// ���g�̍U�����v���C���[�ɓ͂���
	pCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	m_CanAttackPlayer = pCollider->IsHit(pPlayerCollider);
}
