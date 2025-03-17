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

/*�O���錾*/
class Transform;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
private:
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_View;

	// ���_
	DirectX::SimpleMath::Vector3 m_Eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_Target;

	// �����_�ƂȂ���W�ւ̃|�C���^
	Transform* mp_Target;

public:
	/*Main System*/

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		const DirectX::SimpleMath::Vector3& _target = DirectX::SimpleMath::Vector3::Zero
	) noexcept;

	~Camera() noexcept;

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		Transform* pTarget
	) noexcept;

	void Update();

	void ViewUpdate();

	/*Setter*/

	void SetEyePosition   (const DirectX::SimpleMath::Vector3& position);

	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);

	void SetTargetPositionPtr(Transform* pPosition);

	/*Getter*/

	DirectX::SimpleMath::Matrix GetCameraMatrix();

	DirectX::SimpleMath::Vector3 GetEyePosition();

	DirectX::SimpleMath::Vector3 GetTargetPosition();
};

