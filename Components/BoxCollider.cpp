/**
 * @file   BoxCollider.cpp
 *
 * @brief  �{�b�N�X�R���C�_�[�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#include "pch.h"
#include "BoxCollider.h"

// �O���錾
#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
BoxCollider::BoxCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, bool canDraw) noexcept(false)
	: ColliderBace(pScene, ColliderType::Box, name, pTransform, canDraw, SimpleMath::Vector3())
	, m_Siz{ siz }
	, m_Positions{}
{
#if defined(_DEBUG)
	// ���f���̍쐬
	m_Model = GeometricPrimitive::CreateBox(mp_DeviceResources->GetD3DDeviceContext(), siz * 2.f);
#endif
}

/// <summary>
/// Destructor
/// </summary>
BoxCollider::~BoxCollider() noexcept = default;

/// <summary>
/// �d�Ȃ蔻��
/// </summary>
bool BoxCollider::Collider(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Sphare:

	case ColliderType::Box:

	default:
		return false;
	}
}

/// <summary>
/// �T�C�Y�̎擾
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetSiz() const
{
	return m_Siz;
}
