/**
 * @file   BoxCollider.h
 *
 * @brief  �{�b�N�X�R���C�_�[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */

#pragma once
#include "ComponentsBace.h"
#include "DeviceResources.h"
#include "GeometricPrimitive.h"

// �O���錾
class Transform;
class SceneBace;

/// <summary>
/// �{�b�N�X�R���C�_�[�N���X
/// </summary>
class BoxCollider :
    public ComponentsBace
{
private:
	// ���S���W�ƂȂ���W�ւ̃|�C���^
	Transform* mp_Transform;

	// �T�C�Y
	DirectX::SimpleMath::Vector3 m_Siz;

	// �I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_Offset;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// �f�o�b�O�\��
	std::unique_ptr<DirectX::DX11::GeometricPrimitive> m_Model;

	// �\���ݒ�
	bool m_CanDraw;

public:
	/*Main System*/
	BoxCollider(const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, SceneBace* pScene, bool canDraw = true, const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3()) noexcept(false);
	~BoxCollider() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	bool Collider(const BoxCollider& other);

	/*Setter*/
	void CanDraw(bool can) { m_CanDraw = can; }

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;

	DirectX::SimpleMath::Vector3 GetSiz() const;
};

