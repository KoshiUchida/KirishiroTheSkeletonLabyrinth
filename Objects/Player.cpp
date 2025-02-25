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




Transform::Transform() noexcept
	: m_Position{}
	, m_Rotate{}
	, m_Scale(1.0f, 1.0f, 1.0f)
{
}

Transform::~Transform() noexcept = default;

/*Setter Functions*/

void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Position = position;
}

void Transform::SetRotate(const DirectX::SimpleMath::Vector3& rotate)
{
	m_Rotate = rotate;
}

void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_Scale = scale;
}

void Transform::SetScale(float scale)
{
	m_Scale = SimpleMath::Vector3(scale, scale, scale);
}

void Transform::SetPositionX(float x)
{
	m_Position.x = x;
}

void Transform::SetPositionY(float y)
{
	m_Position.y = y;
}

void Transform::SetPositionZ(float z)
{
	m_Position.z = z;
}

void Transform::SetRotateX(float x)
{
	m_Rotate.x = x;
}

void Transform::SetRotateY(float y)
{
	m_Rotate.y = y;
}

void Transform::SetRotateZ(float z)
{
	m_Rotate.z = z;
}

void Transform::SetScaleX(float x)
{
	m_Scale.x = x;
}

void Transform::SetScaleY(float y)
{
	m_Scale.y = y;
}

void Transform::SetScaleZ(float z)
{
	m_Scale.z = z;
}


/*Getter Functions*/

DirectX::SimpleMath::Vector3 Transform::GetPosition() const
{
	return m_Position;
}

DirectX::SimpleMath::Vector3 Transform::GetRotate() const
{
	return m_Rotate;
}

DirectX::SimpleMath::Vector3 Transform::GetScale() const
{
	return m_Scale;
}

float Transform::GetPositionX() const
{
	return m_Position.x;
}

float Transform::GetPositionY() const
{
	return m_Position.y;
}

float Transform::GetPositionZ() const
{
	return m_Position.z;
}

float Transform::GetRotateX() const
{
	return m_Rotate.x;
}

float Transform::GetRotateY() const
{
	return m_Rotate.y;
}

float Transform::GetRotateZ() const
{
	return m_Rotate.z;
}

float Transform::GetScaleX() const
{
	return m_Scale.x;
}

float Transform::GetScaleY() const
{
	return m_Scale.y;
}

float Transform::GetScaleZ() const
{
	return m_Scale.z;
}


/*Addition*/

void Transform::AddPositionX(float x)
{
	m_Position.x += x;
}

void Transform::AddPositionY(float y)
{
	m_Position.y += y;
}

void Transform::AddPositionZ(float z)
{
	m_Position.z += z;
}

void Transform::AddRotateX(float x)
{
	m_Rotate.x += x;
}

void Transform::AddRotateY(float y)
{
	m_Rotate.y += y;
}

void Transform::AddRotateZ(float z)
{
	m_Rotate.z += z;
}

void Transform::AddScaleX(float x)
{
	m_Scale.x += x;
}

void Transform::AddScaleY(float y)
{
	m_Scale.y += y;
}

void Transform::AddScaleZ(float z)
{
	m_Scale.z += z;
}
