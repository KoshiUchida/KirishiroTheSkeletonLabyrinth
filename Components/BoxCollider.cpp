/**
 * @file   BoxCollider.cpp
 *
 * @brief  �{�b�N�X�R���C�_�[�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/18
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
	AddSiz(&m_Positions, m_Siz);

#if defined(_DEBUG)
	// ���f���̍쐬
	m_Model = GeometricPrimitive::CreateBox(mp_DeviceResources->GetD3DDeviceContext(), siz * 5.f);
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
	case ColliderType::Box:
		if (true)
		{
			Positions InsertBox = m_Positions;

			AddSiz(&InsertBox, static_cast<BoxCollider*>(other)->GetSiz());

			MovePositions(&InsertBox, this->GetPosition());

			SimpleMath::Vector3 findPosiiton = other->GetPosition();

			return(
				(InsertBox.min.x <= findPosiiton.x && findPosiiton.x <= InsertBox.max.x) &&
				(InsertBox.min.y <= findPosiiton.y && findPosiiton.y <= InsertBox.max.y) &&
				(InsertBox.min.z <= findPosiiton.z && findPosiiton.z <= InsertBox.max.z));
		}
	case ColliderType::Sphare:

	default:
		return false;
	}
}

/// <summary>
/// �����o�������֐�
/// </summary>
/// <param name="other">�������o�������R���C�_�[</param>
void BoxCollider::Collision(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Box:
		// BoxCollider���m�̉����o������
		if (true)
		{
			// �d�Ȃ�𒲂ׂ�
			if (!Collider(other)) return;

			// ���S���W���m�̍��W�̍������擾
			SimpleMath::Vector3 diffPosition = other->GetPosition() - mp_Transform->GetPosition();

			// �c���p�x���擾
			float vertical{ 0.f };

			// Z�܂���X�̒l��0�������ꍇ�͒l�����߂Ȃ�
			if (diffPosition.z != 0.f && diffPosition.x != 0.f)
				vertical = atan2f(diffPosition.z, diffPosition.x) * 180.f / XM_PI;

			// �����p�x���擾
			float horizontal{ 0.f };

			// Y�܂���X�̒l��0�������ꍇ�͒l�����߂Ȃ�
			if(diffPosition.y != 0.f && diffPosition.x != 0.f)
				horizontal = atan2f(diffPosition.y, diffPosition.x) * 180.f / XM_PI;

			enum class Face
			{
				top,
				buttom,
				left,
				right,
				front,
				back
			};

			Face face;

			// �c�����������\��
			if (vertical == 0.f)
				face = Face::front;
			else if (-45.f <= vertical && vertical <= 45.f)
				face = Face::left;
			else if (45.f <= vertical && vertical <= 135.f)
				face = Face::back;
			else if (-45.f >= vertical && vertical >= -135.f)
				face = Face::front;
			else
				face = Face::right;

			// �����̕�������K�v�ł������������ύX
			if (45.f <= horizontal && horizontal <= 135.f)
				face = Face::top;
			else if (-45.f >= horizontal && horizontal >= -135.f)
				face = Face::buttom;

			// ���̓R���C�_�[�̃T�C�Y���擾
			SimpleMath::Vector3 otherSiz = static_cast<BoxCollider*>(other)->GetSiz();

			// �����ʂɉ����o��
			switch (face)
			{
			case Face::top:
				// �����
				mp_Transform->SetPositionY(other->GetPosition().y + otherSiz.y + m_Siz.y + 0.001f);
				break;
			case Face::buttom:
				// ������
				mp_Transform->SetPositionY(other->GetPosition().y - otherSiz.y - m_Siz.y - 0.001f);
				break;
			case Face::left:
				// ������
				mp_Transform->SetPositionX(other->GetPosition().x - otherSiz.x - m_Siz.x - 0.001f);
				break;
			case Face::right:
				// �E����
				mp_Transform->SetPositionX(other->GetPosition().x + otherSiz.x + m_Siz.x + 0.001f);
				break;
			case Face::front:
				// �O��
				mp_Transform->SetPositionZ(other->GetPosition().z + otherSiz.z + m_Siz.z + 0.001f);
				break;
			case Face::back:
				// ���
				mp_Transform->SetPositionZ(other->GetPosition().z - otherSiz.z - m_Siz.z - 0.001f);
				break;
			default:
				// ERORR
				break;
			}

			break;
		}
	case ColliderType::Sphare:
		// ToDo : ���Ƃ̉����o������
		break;
	default:
		break;
	}

	return;
}

/// <summary>
/// �T�C�Y�̎擾
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetSiz() const
{
	return m_Siz;
}
