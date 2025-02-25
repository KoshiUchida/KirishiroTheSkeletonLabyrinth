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
Player::Player() noexcept
	: m_Transform{}
	, mp_DeviceResources{ nullptr }
	, mp_Proj{ nullptr }
	, mp_States{ nullptr }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player() noexcept = default;

/// <summary>
/// �R���X�g���N�g
/// </summary>
Player::Player(
	DX::DeviceResources* pDeviceResources,
	DirectX::SimpleMath::Matrix* pProj,
	DirectX::CommonStates* pStates) noexcept(false)
	: Player()
{
	mp_DeviceResources = pDeviceResources;
	mp_Proj = pProj;
	mp_States = pStates;

	// ���f���̓ǂݍ���
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
		device, L"Resources\\Models\\Kirishiro.sdkmesh", fx);
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
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
		m_Transform.AddPositionX(-1.5f * elapsedTime);
	}

	// �E�L�[��������Ă��邩
	if (kd.Right)
	{
		m_Transform.AddPositionX(1.5f * elapsedTime);
	}

	// ��L�[��������Ă��邩  
	if (kd.Up)
	{
		m_Transform.AddPositionZ(-1.5f * elapsedTime);
	}

	// ���L�[��������Ă��邩
	if (kd.Down)
	{
		m_Transform.AddPositionZ(1.5f * elapsedTime);
	}

	//m_position += v * 3.0f * elapsedTime;
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw(const SimpleMath::Matrix& view)
{
	// ���[���h�s��
	SimpleMath::Matrix world;

	// ���s�ړ�����s����쐬����
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_Transform.GetPosition());

	// X���ŉ�]����s����쐬����
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_Transform.GetRotateX());

	// Y���ŉ�]����s����쐬����
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_Transform.GetRotateY());

	// Z���ŉ�]����s����쐬����
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(m_Transform.GetRotateZ());

	// �g�傷��s����쐬����
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_Transform.GetScale());

	// ���[���h�s��֓���
	world = trans * rotZ * rotY * rotX * scale;

	// ���f���̕`��
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}


/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	m_Model.reset();
}

Renderer3D::Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false)
	: mp_Transform      { pTransform }
	, mp_DeviceResources{ pScene->GetDeviceResourcesPointer() }
	, mp_Proj           { pScene->GetProjPointer() }
	, mp_States         { pScene->GetCommonStatesPointer() }
{
	// ���f���̓ǂݍ���
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
		device, modelPath, fx);
}

Renderer3D::~Renderer3D() noexcept
{
	m_Model.reset();
}

void Renderer3D::Draw(const DirectX::SimpleMath::Matrix& view)
{
	// ���[���h�s��
	SimpleMath::Matrix world;

	// ���s�ړ�����s����쐬����
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X���ŉ�]����s����쐬����
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y���ŉ�]����s����쐬����
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z���ŉ�]����s����쐬����
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateZ());

	// �g�傷��s����쐬����
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ���[���h�s��֓���
	world = trans * rotZ * rotY * rotX * scale;

	// ���f���̕`��
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}
