/**
 * @file   Player.cpp
 *
 * @brief  �v���C���[�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "Player.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3DWithAnimation.h"
#include "../Components/BoxCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

// �ړ��̐ݒ�l
static constexpr float MoveSpeedSpeed{ 0.1f };
static constexpr float MoveSpeedA    { 0.06f };
static constexpr float MoveSpeedFC   { 0.95f };

// HP�̍ő�l
static constexpr int MaxHP{ 100 };

// �U���̃N�[���^�C��
static constexpr float SetAttackCooltime{ 1.7f };

/// <summary>
/// �R���X�g���N�g
/// </summary>
Player::Player(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name),
	m_MoveSpeed{ MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC },
	m_IsAttack { false },
	m_CanAttack{ true },
	m_AttackCooltime{ SetAttackCooltime },
	m_HP       { MaxHP },
	m_Die      { false }
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3DWithAnimation>(pScene, "Renderer3D", pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

	pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim");

	static constexpr bool  ShowCollider{ false };
	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f), ShowCollider));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.3f, 0.1f, 0.3f)));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	pDamageCollider->SetOffset(SimpleMath::Vector3(0.7f, 0.f, 0.f));
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Process(float elapsedTime)
{
	m_AttackCooltime -= elapsedTime;
	if (m_AttackCooltime < 0.f)
	{
		m_AttackCooltime = 0.f;
		m_CanAttack = true;
		if (m_IsAttack)
		{
			Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

			pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim");
		}
		m_IsAttack = false;
	}
	else
		m_CanAttack = false;

	// �ړ�����
	Move(elapsedTime);

	// �U������
	Attack();
}

/// <summary>
/// �_���[�W�����֐�
/// </summary>
void Player::Damage(int damage)
{
	m_HP -= damage;
	
	if (m_HP < 0)
		m_HP = 0;

	m_Die = (m_HP == 0);
}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move(float elapsedTime)
{
	// �L�[�{�[�h�̓��͂��擾
	Keyboard::State kb = Keyboard::Get().GetState();

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// �R���g���[���̒l
	float cx = { 0.f };
	float cy = { 0.f };

	// ���L�[��������Ă��邩
	if (kb.Left || kb.A)
	{
		cx = -1.f;
	}
	// �E�L�[��������Ă��邩
	if (kb.Right || kb.D)
	{
		cx = 1.f;
	}
	// ��L�[��������Ă��邩  
	if (kb.Up || kb.W)
	{
		cy = 1.f;
	}
	// ���L�[��������Ă��邩
	if (kb.Down || kb.S)
	{
		cy = -1.f;
	}

	// �ړ����̏���
	if (kb.Left || kb.Right || kb.Up || kb.Down ||
		kb.A    || kb.D     || kb.W  || kb.S)
	{
		m_MoveSpeed.Up(elapsedTime);

		pTransform->SetRotateY(std::atan2f(cy, cx));
	}
	// ��~���̏���
	else
	{
		m_MoveSpeed.Stop(elapsedTime);
	}

	// ���x�x�N�g��
	SimpleMath::Vector3 speed(m_MoveSpeed.Get(), 0.f, 0.f);

	// Y���ŉ�]����s����쐬
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(pTransform->GetRotateY());
	speed = SimpleMath::Vector3::Transform(speed, rotY);

	// ���W�̍X�V����
	pTransform->AddPosition(speed);

}

/// <summary>
/// �U������
/// </summary>
void Player::Attack()
{
	// �L�[�{�[�h�̓��͂��擾
	Keyboard::State kb = Keyboard::Get().GetState();

	// �U���L�[��������Ă��邩
	if (m_CanAttack && (kb.Z || kb.J))
	{
		if (!m_IsAttack)
		{
			Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

			pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroAttack.sdkmesh_anim");
		}
		m_IsAttack = true;

		m_AttackCooltime = SetAttackCooltime;
	}
}

/// <summary>
/// �U�������Ă��邩���擾�֐�
/// </summary>
bool Player::IsAttack() const noexcept
{
	return m_IsAttack;
}

/// <summary>
/// ���S�������ǂ����̎擾�֐�
/// </summary>
bool Player::Die() const noexcept
{
	return m_Die;
}

/// <summary>
/// HP�̎擾�֐�
/// </summary>
int Player::GetHP() const noexcept
{
	return m_HP;
}

/// <summary>
/// �ő�HP�̎擾�֐�
/// </summary>
int Player::GetMaxHP() const noexcept
{
	return MaxHP;
}

