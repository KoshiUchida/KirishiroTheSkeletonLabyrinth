/**
 * @file   Player.cpp
 *
 * @brief  �v���C���[�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/21
 */

#include "pch.h"
#include "Player.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

// �ړ��̐ݒ�l
static constexpr float MoveSpeedSpeed{ 5.f };
static constexpr float MoveSpeedA    { 4.5f };
static constexpr float MoveSpeedFC   { 0.95f };

/// <summary>
/// �R���X�g���N�g
/// </summary>
Player::Player(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
	, m_MoveSpeed{ MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC }
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));
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
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Process(float elapsedTime)
{
	// �ړ�����
	Move(elapsedTime);
}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move(float elapsedTime)
{
	// �L�[�{�[�h�̓��͂��擾
	Keyboard::State kd = Keyboard::Get().GetState();

	// �R���g���[���̒l
	float cx = { 0.f };
	float cy = { 0.f };

	// ���L�[��������Ă��邩
	if (kd.Left)
	{
		cx -= 1.f;
	}
	// �E�L�[��������Ă��邩
	if (kd.Right)
	{
		cx += 1.f;
	}
	// ��L�[��������Ă��邩  
	if (kd.Up)
	{
		cy += 1.f;
	}
	// ���L�[��������Ă��邩
	if (kd.Down)
	{
		cy -= 1.f;
	}

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// �ړ����̏���
	if (kd.Left || kd.Right || kd.Up || kd.Down)
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
	pTransform->AddPosition(speed * elapsedTime);

}

