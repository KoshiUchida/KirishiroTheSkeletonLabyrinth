/**
 * @file   ColliderBace.h
 *
 * @brief  �R���C�_�[���N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#pragma once
#include "ComponentsBace.h"
#include "GeometricPrimitive.h"
#include "DeviceResources.h"

// �O���錾
class SceneBace;
class Transform;

/// <summary>
/// �R���C�_�[���N���X
/// </summary>
class ColliderBace:
	public ComponentsBace
{
protected:
	// �R���C�_�[�^�C�v�̑S��
	enum class ColliderType
	{
		Sphare,
		Box,
	};

	// �R���C�_�[�^�C�v
	ColliderType m_Type;
	
	// ���S�ƂȂ�g�����X�t�H�[���ւ̃|�C���^
	Transform* mp_Transform;

	// �`��̋���
	bool m_CanDraw;

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
	ColliderBace(SceneBace* pScene, ColliderType type, const std::string& name, Transform* pTransform, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false);
	virtual ~ColliderBace() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	virtual bool Collider(ColliderBace* other) = 0;

	/*Setter*/
	void CanDraw(bool can) { m_CanDraw = can; }

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;
	                ColliderType GetType()     const { return m_Type; }

protected:
	// ���_�̍��W�Q�\����
	struct Positions
	{
		DirectX::SimpleMath::Vector3 max;
		DirectX::SimpleMath::Vector3 min;
		DirectX::SimpleMath::Vector3 p1;
		DirectX::SimpleMath::Vector3 p2;
		DirectX::SimpleMath::Vector3 p3;
		DirectX::SimpleMath::Vector3 p4;
		DirectX::SimpleMath::Vector3 p5;
		DirectX::SimpleMath::Vector3 p6;
	};

	// ���_�̍��W�Q�ւ̓���
	void AddSiz(Positions* pPositions, const DirectX::SimpleMath::Vector3& addSiz);
};

