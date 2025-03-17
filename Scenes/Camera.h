/**
 * @file   Camera.h
 *
 * @brief  �J�����N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#pragma once

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
private:
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;

public:
	/*Main System*/

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		const DirectX::SimpleMath::Vector3& _target = DirectX::SimpleMath::Vector3::Zero
	);

	void ViewUpdate();

	/*Setter*/

	void SetEyePosition   (const DirectX::SimpleMath::Vector3& position);

	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);

	/*Getter*/

	DirectX::SimpleMath::Matrix GetCameraMatrix();

	DirectX::SimpleMath::Vector3 GetEyePosition();

	DirectX::SimpleMath::Vector3 GetTargetPosition();
};

