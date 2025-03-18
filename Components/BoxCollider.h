/**
 * @file   BoxCollider.h
 *
 * @brief  �{�b�N�X�R���C�_�[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#pragma once
#include "ColliderBace.h"
#include "GeometricPrimitive.h"

// �O���錾
class Transform;
class SceneBace;

/// <summary>
/// �{�b�N�X�R���C�_�[�N���X
/// </summary>
class BoxCollider :
    public ColliderBace
{
private:
	// �T�C�Y
	DirectX::SimpleMath::Vector3 m_Siz;

	// ���_�̍��W�Q
	Positions m_Positions;
public:
	/*Main System*/
	BoxCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, bool canDraw = true) noexcept(false);
	~BoxCollider() noexcept;

	bool Collider(ColliderBace* other) override final;

	void Collision(ColliderBace* other) override final;

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetSiz() const;
};

