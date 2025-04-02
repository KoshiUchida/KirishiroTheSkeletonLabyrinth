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
static constexpr float RotateSpeedSpeed{ XM_PI / 24.f };
static constexpr float RotateSpeedA{ XM_PI / 26.f };
static constexpr float RotateSpeedFC{ 0.95f };

// ��]��~�͈̔�
static constexpr float RotateRange{ XM_PI / 24.f };

// �ړ��̐ݒ�l
static constexpr float MoveSpeedSpeed{ 0.05f };
static constexpr float MoveSpeedA{ 0.03f };
static constexpr float MoveSpeedFC{ 0.95f };

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const string& name, const SimpleMath::Vector3& position) noexcept :
	ObjectBace(pScene, name),
	m_Action{ CurrentCourseOfAction::NONE },
	m_SpownPosition  { position },
	m_PlayerFound    { false },
	m_SpawnPointFar  { false },
	m_RotateSpeed    { RotateSpeedSpeed, RotateSpeedA, RotateSpeedFC },
	m_RotatePlusMinus{ 0.f },
	m_CanAttackPlayer{ false },
	m_MoveSpeed      { MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC }
{
	AddComponent(make_unique<Transform>());

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ���W�̐ݒ�
	pTransform->SetPosition(m_SpownPosition);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	static constexpr bool  ShowCollider{ false };
	AddComponent(make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f), ShowCollider));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.2f, 0.1f, 0.2f)));
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	static constexpr float OffsetDamageCollider{ 0.7f };
	pDamageCollider->SetOffset(SimpleMath::Vector3(OffsetDamageCollider, 0.f, 0.f));

	static constexpr float PerceptionRange    { 5.f };
	static constexpr bool  ShowPerceptionRange{ false };
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
	// ���g�̍��W���擾
	Transform* thisTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// �^�[�Q�b�g�̂������
	float targetDirection = thisTransform->GetRotateY();

	// �������~�߂邩
	bool stop{ false };

	switch (m_Action)
	{
	case Enemy::CurrentCourseOfAction::NONE:
		{
			// �X�|�[���n�_�������擾
			if (m_SpawnPointFar)
				targetDirection = XM_PI / -2.f + atan2f((m_SpownPosition.x - thisTransform->GetPositionX()), (m_SpownPosition.z - thisTransform->GetPositionZ()));

			stop = !m_SpawnPointFar;

			// �v���C���[��m�o�����ꍇCHASE��
			if (m_PlayerFound)
				m_Action = CurrentCourseOfAction::CHASE;
			break;
		}
	case Enemy::CurrentCourseOfAction::CHASE:
		{
			// �v���C���[�̃g�����X�t�H�[�����擾
			Transform* pPlayerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

			// �v���C���[�̂���������擾
			targetDirection = XM_PI / -2.f + atan2f((pPlayerTransform->GetPositionX() - thisTransform->GetPositionX()), (pPlayerTransform->GetPositionZ() - thisTransform->GetPositionZ()));

			// �����A�U�����ł���ꍇ�ɗ����~�܂�
			stop = m_CanAttackPlayer;

			// �v���C���[���m�o�O�ɂ���ꍇNONE��
			if (!m_PlayerFound)
				m_Action = CurrentCourseOfAction::NONE;

			break;
		}
	default:
		// ERORR : ���肦�Ȃ����� m_Action�̒l���m�F���Ă��������B
		break;
	}

	// ���݂̕�������̍����ʏ���
	if (thisTransform->GetRotateY() >= targetDirection - RotateRange / 2.f && thisTransform->GetRotateY() <= targetDirection + RotateRange / 2.f)
		m_RotateSpeed.Stop(elapsedTime);

	else
	{
		m_RotateSpeed.Up(elapsedTime);

		if (thisTransform->GetRotateY() < targetDirection - RotateRange / 2.f)
			m_RotatePlusMinus = 1.f;
		else if (thisTransform->GetRotateY() > targetDirection + RotateRange / 2.f)
			m_RotatePlusMinus = -1.f;
	}

	// ���g�̉�]
	if (m_RotateSpeed.Get() != 0.f && m_RotatePlusMinus != 0.f)
		thisTransform->AddRotateY(m_RotateSpeed.Get() * m_RotatePlusMinus);

	//�����A�U�����ł����Ԃł͂Ȃ������ꍇ
	if (!stop)
	{
		m_MoveSpeed.Up(elapsedTime);
	}
	else
	{
		m_MoveSpeed.Stop(elapsedTime);
	}

	if (m_MoveSpeed.Get() != 0.f)
	{

		// ���x�x�N�g��
		SimpleMath::Vector3 speed(m_MoveSpeed.Get(), 0.f, 0.f);

		// Y���ŉ�]����s����쐬
		SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(thisTransform->GetRotateY());
		speed = SimpleMath::Vector3::Transform(speed, rotY);

		// ���W�̍X�V����
		thisTransform->AddPosition(speed);
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

	// �m�o�͈͂̎擾
	SphereCollider* pPerceptionRange = static_cast<SphereCollider*>(GetComponentPtr("PerceptionRange"));

	// �v���C���[���m�o�͈͂ɂ��邩
	m_PlayerFound = pPerceptionRange->IsHit(pPlayerCollider->GetPosition());

	// �X�|�[���n�_���痣�ꂷ���Ă��Ȃ���
	m_SpawnPointFar = !(pPerceptionRange->IsHit(m_SpownPosition));

	// ���g�̍U�����v���C���[�ɓ͂���
	pCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	m_CanAttackPlayer = pCollider->IsHit(pPlayerCollider);
}
