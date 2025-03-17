/**
 * @file   Camera.h
 *
 * @brief  �J�����N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#include "pch.h"
#include "Camera.h"

/*�O���錾*/
#include "../Components/Transform.h"

using namespace DirectX;

/*Main System*/

/// <summary>
/// Constructor
/// </summary>
/// <param name="_eye">���_�̍��W</param>
/// <param name="_target">���_�̍��W</param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, const DirectX::SimpleMath::Vector3& _target) noexcept
	: m_Eye   { _eye }
	, m_Target{ _target }
	, m_View{}
	, mp_Target{ nullptr }
{
}

/// <summary>
/// Destructor
/// </summary>
Camera::~Camera() noexcept = default;

/// <summary>
/// 
/// </summary>
/// <param name="_eye"></param>
/// <param name="pTarget"></param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, Transform* pTarget) noexcept
	: m_Eye    { _eye }
	, m_Target { SimpleMath::Vector3::Zero}
	, m_View   {}
	, mp_Target{ pTarget }
{
}

/// <summary>
/// �X�V����
/// </summary>
void Camera::Update()
{
	ViewUpdate();
}

/// <summary>
/// �r���[�s��̍X�V����
/// </summary>
void Camera::ViewUpdate()
{
	if (mp_Target)
	{
		m_View = SimpleMath::Matrix::CreateLookAt(mp_Target->GetPosition() + m_Eye, mp_Target->GetPosition(), SimpleMath::Vector3::UnitY);
	}
	else
	{
		m_View = SimpleMath::Matrix::CreateLookAt(m_Eye, m_Target, SimpleMath::Vector3::UnitY);
	}
}


/*Setter*/

/// <summary>
/// ���_�̐ݒ�֐�
/// </summary>
/// <param name="position">���_�̍��W</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Eye = position;
}

/// <summary>
/// ���_�̐ݒ�֐�
/// </summary>
/// <param name="position">���_�̍��W</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Target = position;
}

/// <summary>
/// �����_�|�C���^�̐ݒ�֐�
/// </summary>
/// <param name="pPosition">�����_�ƂȂ���W�ւ̃|�C���^</param>
void Camera::SetTargetPositionPtr(Transform* pPosition)
{
	mp_Target = pPosition;
}



/*Getter*/

/// <summary>
/// �f�o�b�O�J�����̃r���[�s��̎擾�֐�
/// </summary>
/// <returns>�r���[�s��</returns>
DirectX::SimpleMath::Matrix Camera::GetCameraMatrix()
{
	return m_View;
}

/// <summary>
/// �J�����̈ʒu�̎擾�֐�
/// </summary>
/// <returns>���_�̈ʒu</returns>
DirectX::SimpleMath::Vector3 Camera::GetEyePosition()
{
	return m_Eye;
}


/// <summary>
/// �f�o�b�O�J�����̒����_�̎擾�֐�
/// </summary>
/// <returns>�����_�̈ʒu</returns>
DirectX::SimpleMath::Vector3 Camera::GetTargetPosition()
{
	return m_Target;
}

