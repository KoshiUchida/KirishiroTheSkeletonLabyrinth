/**
 * @file   Player.h
 *
 * @brief  �v���C���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#pragma once
#include <memory>
#include "DeviceResources.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;

	// �����i���W�A���l�j
	DirectX::SimpleMath::Vector3 m_rotate;

	// �傫��
	DirectX::SimpleMath::Vector3 m_scale;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// ���ʃX�e�[�g
	DirectX::CommonStates* mp_States;

public:
	// Main System
	Player() noexcept;
	~Player() noexcept;

	Player
	(
		DX::DeviceResources* pDeviceResources,
		DirectX::SimpleMath::Matrix* pProj,
		DirectX::CommonStates* pStates
	);

	void Initialize();
	void Update(float elapsedTime);
	void Draw(const DirectX::SimpleMath::Matrix& view);
	void Finalize();

	// Setter
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	void SetRotate  (const DirectX::SimpleMath::Vector3& rotate);
	void SetScale   (const DirectX::SimpleMath::Vector3& scale);

	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);

	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	// Getter
	DirectX::SimpleMath::Vector3 GetPosition() const;
	DirectX::SimpleMath::Vector3 GetRotate()   const;
	DirectX::SimpleMath::Vector3 GetScale()    const;

	float GetPositionX() const;
	float GetPositionY() const;
	float GetPositionZ() const;

	float GetRotateX() const;
	float GetRotateY() const;
	float GetRotateZ() const;

	float GetScaleX() const;
	float GetScaleY() const;
	float GetScaleZ() const;
};

