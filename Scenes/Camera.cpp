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

using namespace DirectX;

/*Main System*/

/// <summary>
/// Constructor
/// </summary>
/// <param name="_eye">���_�̍��W</param>
/// <param name="_target">���_�̍��W</param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, const DirectX::SimpleMath::Vector3& _target)
	: m_eye   { _eye }
	, m_target{ _target }
	, m_view{}
{
	ViewUpdate();
}

/// <summary>
/// �r���[�s��̍X�V����
/// </summary>
void Camera::ViewUpdate()
{
	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, SimpleMath::Vector3::UnitY);
}


/*Setter*/

/// <summary>
/// ���_�̐ݒ�֐�
/// </summary>
/// <param name="position">���_�̍��W</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_eye = position;

	ViewUpdate();
}

/// <summary>
/// ���_�̐ݒ�֐�
/// </summary>
/// <param name="position">���_�̍��W</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_target = position;

	ViewUpdate();
}



/*Getter*/

/// <summary>
/// �f�o�b�O�J�����̃r���[�s��̎擾�֐�
/// </summary>
/// <returns>�r���[�s��</returns>
DirectX::SimpleMath::Matrix Camera::GetCameraMatrix()
{
	return m_view;
}

/// <summary>
/// �J�����̈ʒu�̎擾�֐�
/// </summary>
/// <returns>���_�̈ʒu</returns>
DirectX::SimpleMath::Vector3 Camera::GetEyePosition()
{
	return m_eye;
}


/// <summary>
/// �f�o�b�O�J�����̒����_�̎擾�֐�
/// </summary>
/// <returns>�����_�̈ʒu</returns>
DirectX::SimpleMath::Vector3 Camera::GetTargetPosition()
{
	return m_target;
}

