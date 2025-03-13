/**
 * @file   BoxCollider.cpp
 *
 * @brief  �{�b�N�X�R���C�_�[�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/13
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
BoxCollider::BoxCollider(const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, SceneBace* pScene, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false)
	: ComponentsBace(ComponentsBace::Tags::Collider, name)
	, mp_Transform       { pTransform }
	, m_Offset           { offset }
	, m_Siz              { siz }
	, mp_DeviceResources { pScene->GetDeviceResourcesPointer() }
	, mp_Proj            { pScene->GetProjPointer() }
	, m_CanDraw          { canDraw }
{
	m_Model = GeometricPrimitive::CreateBox(mp_DeviceResources->GetD3DDeviceContext(), siz);
}

/// <summary>
/// Destructor
/// </summary>
BoxCollider::~BoxCollider() noexcept = default;

/// <summary>
/// �`�揈��
/// </summary>
void BoxCollider::Render(const DirectX::SimpleMath::Matrix& view)
{
	if (!m_CanDraw)
		return;

#if defined(_DEBUG)
	// ���[���h�s��
	SimpleMath::Matrix world;

	// ���s�ړ�����s����쐬����
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X���ŉ�]����s����쐬����
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y���ŉ�]����s����쐬����
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z���ŉ�]����s����쐬����
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateZ());

	// �g�傷��s����쐬����
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ���[���h�s��֓���
	world = trans * rotZ * rotY * rotX * scale;

	m_Model->Draw(world, view, *mp_Proj);
#endif
}

/// <summary>
/// �d�Ȃ蔻��
/// </summary>
bool BoxCollider::Collider(const BoxCollider& other)
{
	return false;
}

/// <summary>
/// ���W�̎擾
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// �T�C�Y�̎擾
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetSiz() const
{
	return m_Siz;
}
