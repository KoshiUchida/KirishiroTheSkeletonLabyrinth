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

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/SphereCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�g
/// </summary>
Player::Player(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	AddComponent(std::make_unique<SphereCollider>("Collider", pTransform, 1.f, mp_Scene, false));
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
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetScale(0.35f);
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Process(float elapsedTime)
{
	// �L�[�{�[�h�̓��͂��擾
	auto kd = Keyboard::Get().GetState();

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	//float rotateSpeed = 75.f;

	//// ���x�x�N�g��
	//SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

	//// Y���ŉ�]����s����쐬����
	//SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);
	//v = SimpleMath::Vector3::Transform(v, rotY);

	// ���L�[��������Ă��邩
	if (kd.Left)
	{
		pTransform->AddPositionX(-2.5f * elapsedTime);
	}

	// �E�L�[��������Ă��邩
	if (kd.Right)
	{
		pTransform->AddPositionX(2.5f * elapsedTime);
	}

	// ��L�[��������Ă��邩  
	if (kd.Up)
	{
		pTransform->AddPositionZ(-2.5f * elapsedTime);
	}

	// ���L�[��������Ă��邩
	if (kd.Down)
	{
		pTransform->AddPositionZ(2.5f * elapsedTime);
	}

	//m_position += v * 3.0f * elapsedTime;

	// �d�Ȃ菈��
	if (
		static_cast<SphereCollider*>(GetComponentPtr("Collider"))
		->Collider(
			*static_cast<SphereCollider*>(GetObjectPtr("Sample")->GetComponentPtr("Collider"))
		))
	{
		pTransform->SetPosition(SimpleMath::Vector3());
	}
}

