/**
 * @file   SphereCollider.cpp
 *
 * @brief  ���R���C�_�[�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/15
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
SphereCollider::SphereCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, float radius, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept
	: ColliderBace(pScene, ColliderType::Sphare, name, pTransform, canDraw, offset)
	, m_Radius{ radius }
{
#if defined(_DEBUG)
	m_Model = GeometricPrimitive::CreateSphere(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext(), m_Radius * 2.f);
#endif
}

/// <summary>
/// Destructor
/// </summary>
SphereCollider::~SphereCollider() noexcept = default;

/// <summary>
/// �d�Ȃ蔻��
/// </summary>
/// <param name="other">�d�Ȃ�𒲂ׂ�R���C�_�[</param>
bool SphereCollider::IsHit(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Sphare:
		if (true)
		{
			// �d�Ȃ鋗�������߂�
			float radiusSum = this->GetRadius() + static_cast<SphereCollider*>(other)->GetRadius();

			// �R���C�_�[���m�̋��������߂�
			SimpleMath::Vector3 positionA = this->GetPosition();
			SimpleMath::Vector3 positionB = other->GetPosition();
			float x = positionB.x - positionA.x;
			float y = positionB.y - positionA.y;
			float z = positionB.z - positionA.z;
			float intersect = sqrtf(x * x + y * y + z * z);

			// �R���C�_�[�̏d�Ȃ�𒲂ׂ�
			return intersect <= radiusSum;
		}
	case ColliderType::Box:
		if (true)
		{
		}
	default:
		return false;
	}
}

/// <summary>
/// �_�Ƃ̏d�Ȃ菈��
/// </summary>
bool SphereCollider::IsHit(const DirectX::SimpleMath::Vector3& other)
{
	// ���������߂�
	SimpleMath::Vector3 positionA = this->GetPosition();
	float x = other.x - positionA.x;
	float y = other.y - positionA.y;
	float z = other.z - positionA.z;
	float intersect = sqrtf(x * x + y * y + z * z);

	// �_�Ƃ̏d�Ȃ�𒲂ׂ�
	return intersect <= m_Radius;
}

void SphereCollider::Collision(ColliderBace* other)
{
	other;

	// ToDo:�����o������
}

/// <summary>
/// ���a�̐ݒ�֐�
/// </summary>
void SphereCollider::SetRadius(float radius)
{
	m_Radius = radius;
}

/// <summary>
/// ���a�̎擾
/// </summary>
/// <returns>���a</returns>
float SphereCollider::GetRadius() const
{
	return m_Radius;
}
