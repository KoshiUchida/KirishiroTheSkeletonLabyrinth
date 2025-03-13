
/**
 * @file   SphereCollider.cpp
 *
 * @brief  ���R���C�_�[�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/10
 */

#include "pch.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
/// <param name="pTransform">���S���W�ƂȂ�g�����X�t�H�[���ւ̃|�C���^</param>
/// <param name="radius">���a</param>
/// <param name="offset">�I�t�Z�b�g</param>
SphereCollider::SphereCollider(const std::string& name, Transform* pTransform, float radius, SceneBace* pScene, const DirectX::SimpleMath::Vector3& offset) noexcept
	: ComponentsBace(Tags::Collider, name)
	, mp_Transform{ pTransform }
	, m_Radius    { radius }
	, m_Offset    { offset }
{
	mp_DeviceResources = pScene->GetDeviceResourcesPointer();
	mp_Proj = pScene->GetProjPointer();
	m_Model = GeometricPrimitive::CreateSphere(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext(), m_Radius * 2.f);
}

/// <summary>
/// Destructor
/// </summary>
SphereCollider::~SphereCollider() noexcept
{
	mp_Transform       = nullptr;
	mp_DeviceResources = nullptr;
	mp_Proj            = nullptr;
	m_Model.reset();
}

/// <summary>
/// �`�揈��
/// </summary>
void SphereCollider::Render(const DirectX::SimpleMath::Matrix& view)
{
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
/// <param name="other">�d�Ȃ�𒲂ׂ�R���C�_�[</param>
bool SphereCollider::Collider(const SphereCollider& other)
{
	// �d�Ȃ鋗�������߂�
	float radiusSum = this->GetRadius() + other.GetRadius();

	// �R���C�_�[���m�̋��������߂�
	SimpleMath::Vector3 positionA = this->GetPosition();
	SimpleMath::Vector3 positionB = other.GetPosition();
	float x = positionB.x - positionA.x;
	float y = positionB.y - positionA.y;
	float z = positionB.z - positionA.z;
	float intersect = sqrtf(x * x + y * y + z * z);

	// �R���C�_�[�̏d�Ȃ�𒲂ׂ�
	return intersect <= radiusSum;
}

/// <summary>
/// ���S���W�̎擾
/// </summary>
/// <returns>���S���W</returns>
DirectX::SimpleMath::Vector3 SphereCollider::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// ���a�̎擾
/// </summary>
/// <returns>���a</returns>
float SphereCollider::GetRadius() const
{
	return m_Radius;
}
