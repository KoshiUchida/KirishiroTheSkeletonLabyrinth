/**
 * @file   SphereCollider.h
 *
 * @brief  ���R���C�_�[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/10
 */

#pragma once
#include "ComponentsBace.h"
#include "DeviceResources.h"
#include "GeometricPrimitive.h"

class Transform;
class SceneBace;

/// <summary>
/// ���R���C�_�[�N���X
/// </summary>
class SphereCollider
	: public ComponentsBace
{
private:
	// ���S���W�ƂȂ���W�ւ̃|�C���^
	Transform* mp_Transform;

	// ���a
	float m_Radius;

	// �I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_Offset;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// �f�o�b�O�\��
	std::unique_ptr<DirectX::DX11::GeometricPrimitive> m_Model;
	
public:
	/*Main System*/
	SphereCollider(const std::string& name, Transform* pTransform, float radius, SceneBace* pScene, const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3()) noexcept;
	~SphereCollider() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	bool Collider(const SphereCollider& other);

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;
	float GetRadius() const;
};

