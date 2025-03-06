/**
 * @file   Transform.cpp
 *
 * @brief  �v���C���[�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#include "pch.h"
#include "Player.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�g
/// </summary>
Player::Player(SceneBace* pScene) noexcept(false)
	: ObjectBace(pScene)
	, m_Renderer(pScene, m_Transform.get(), L"Resources\\Models\\Kirishiro.sdkmesh")
{
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
	this->m_Transform->SetScale(0.35f);
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update(float elapsedTime)
{
	// �L�[�{�[�h�̓��͂��擾
	auto kd = Keyboard::Get().GetState();

	//float rotateSpeed = 75.f;

	//// ���x�x�N�g��
	//SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

	//// Y���ŉ�]����s����쐬����
	//SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);
	//v = SimpleMath::Vector3::Transform(v, rotY);

	// ���L�[��������Ă��邩
	if (kd.Left)
	{
		m_Transform->AddPositionX(-1.5f * elapsedTime);
	}

	// �E�L�[��������Ă��邩
	if (kd.Right)
	{
		m_Transform->AddPositionX(1.5f * elapsedTime);
	}

	// ��L�[��������Ă��邩  
	if (kd.Up)
	{
		m_Transform->AddPositionZ(-1.5f * elapsedTime);
	}

	// ���L�[��������Ă��邩
	if (kd.Down)
	{
		m_Transform->AddPositionZ(1.5f * elapsedTime);
	}

	//m_position += v * 3.0f * elapsedTime;
}

