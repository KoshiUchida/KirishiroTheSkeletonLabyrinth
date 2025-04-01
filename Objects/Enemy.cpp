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

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const string& name, const SimpleMath::Vector3& position) noexcept :
	ObjectBace(pScene, name),
	m_Action{ CurrentCourseOfAction::NONE },
	m_SpownPosition{ position }
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

	static constexpr float PerceptionRange    { 9.f };
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
	// �x�����p
	elapsedTime;

	Move();

	Collision();
}

/// <summary>
/// �ړ��֌W����
/// </summary>
void Enemy::Move()
{
	switch (m_Action)
	{
	case Enemy::CurrentCourseOfAction::NONE:
		break;
	case Enemy::CurrentCourseOfAction::CHASE:
		break;
	default:
		// ERORR : ���肦�Ȃ����� m_Action�̒l���m�F���Ă��������B
		break;
	}
}

/// <summary>
/// �R���C�_�[�֌W����
/// </summary>
void Enemy::Collision()
{
	// ���g�̃R���C�_�[���擾
	ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));

	// �v���C���[�̍U���ɑ΂��鏈��
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	// �v���C���[�̃R���C�_�[�ւ̃|�C���^
	ColliderBace* pPlayerCollider;

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
}
