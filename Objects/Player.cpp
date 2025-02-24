/**
 * @file   Player.cpp
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
	: m_position(0.0f, 0.0f, 0.0f)
	, m_rotate  (0.0f, 0.0f, 0.0f)
	, m_scale   (1.0f, 1.0f, 1.0f)
	, mp_DeviceResources{ nullptr }
	, mp_Proj           { nullptr }
	, mp_States         { nullptr }
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
	      DirectX::CommonStates* pStates)
	: Player()
{
	mp_DeviceResources = pDeviceResources;
	mp_Proj            = pProj;
	mp_States          = pStates;

	// ���f���̓ǂݍ���
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_model = Model::CreateFromSDKMESH(
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
		m_position.x += 3.0f * elapsedTime;
	}

	// �E�L�[��������Ă��邩
	if (kd.Right)
	{
		m_position.x -= 3.0f * elapsedTime;
	}

	// ��L�[��������Ă��邩  
	if (kd.Up)
	{
		m_position.z += 3.0f * elapsedTime;
	}

	// ���L�[��������Ă��邩
	if (kd.Down)
	{
		m_position.z -= 3.0f * elapsedTime;
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
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_position);

	// X���ŉ�]����s����쐬����
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_rotate.x);

	// Y���ŉ�]����s����쐬����
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);

	// Z���ŉ�]����s����쐬����
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(m_rotate.z);

	// �g�傷��s����쐬����
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_scale);

	// ���[���h�s��֓���
	world = trans * rotZ * rotY * rotX * scale;

	// ���f���̕`��
	m_model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}


/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	m_model.reset();
}


/*Setter Functions*/

void Player::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

void Player::SetRotate(const DirectX::SimpleMath::Vector3& rotate)
{
	m_rotate = rotate;
}

void Player::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}

void Player::SetPositionX(float x)
{
	m_position.x = x;
}

void Player::SetPositionY(float y)
{
	m_position.y = y;
}

void Player::SetPositionZ(float z)
{
	m_position.z = z;
}

void Player::SetRotateX(float x)
{
	m_rotate.x = x;
}

void Player::SetRotateY(float y)
{
	m_rotate.y = y;
}

void Player::SetRotateZ(float z)
{
	m_rotate.z = z;
}

void Player::SetScaleX(float x)
{
	m_scale.x = x;
}

void Player::SetScaleY(float y)
{
	m_scale.y = y;
}

void Player::SetScaleZ(float z)
{
	m_scale.z = z;
}


/*Getter Functions*/

DirectX::SimpleMath::Vector3 Player::GetPosition() const
{
	return m_position;
}

DirectX::SimpleMath::Vector3 Player::GetRotate() const
{
	return m_rotate;
}

DirectX::SimpleMath::Vector3 Player::GetScale() const
{
	return m_scale;
}

float Player::GetPositionX() const
{
	return m_position.x;
}

float Player::GetPositionY() const
{
	return m_position.y;
}

float Player::GetPositionZ() const
{
	return m_position.z;
}

float Player::GetRotateX() const
{
	return m_rotate.x;
}

float Player::GetRotateY() const
{
	return m_rotate.y;
}

float Player::GetRotateZ() const
{
	return m_rotate.z;
}

float Player::GetScaleX() const
{
	return m_scale.x;
}

float Player::GetScaleY() const
{
	return m_scale.y;
}

float Player::GetScaleZ() const
{
	return m_scale.z;
}
