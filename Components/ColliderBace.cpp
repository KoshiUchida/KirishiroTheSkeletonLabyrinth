/**
 * @file   ColliderBace.cpp
 *
 * @brief  �R���C�_�[���N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#include "pch.h"
#include "ColliderBace.h"

// �O���錾
#include "../Scenes/SceneBace.h"
#include "../Components/Transform.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
ColliderBace::ColliderBace(SceneBace* pScene, ColliderType type, const std::string& name, Transform* pTransform, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false)
	: ComponentsBace(ComponentsBace::Tags::Collider, name)
	, mp_Transform{ pTransform }
	, m_Type      { type }
	, m_CanDraw   { canDraw }
	, m_Offset    { offset }
	, mp_Proj           { nullptr }
	, mp_DeviceResources{ nullptr }
{
#if defined(_DEBUG)
	mp_Proj            = pScene->GetProjPointer();
	mp_DeviceResources = pScene->GetDeviceResourcesPointer();
#endif
}

/// <summary>
/// Destructor
/// </summary>
ColliderBace::~ColliderBace() noexcept = default;

void ColliderBace::Render(const DirectX::SimpleMath::Matrix& view)
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
	world =  rotZ * rotY * rotX * scale * trans;

	m_Model->Draw(world, view, *mp_Proj, Colors::Red);
#endif
}

/// <summary>
/// ���W�̎擾
/// </summary>
DirectX::SimpleMath::Vector3 ColliderBace::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// ���W�Q�ւ̓���
/// </summary>
/// <param name="pPositions">���͂�����W�Q�ւ̃|�C���^</param>
/// <param name="addSiz">���̓T�C�Y</param>
void ColliderBace::AddSiz(Positions* pPositions, const DirectX::SimpleMath::Vector3& addSiz)
{
	if (!pPositions)
		return;

	pPositions->max += addSiz;
	pPositions->min -= addSiz;

	pPositions->p1.x += addSiz.x;
	pPositions->p1.y -= addSiz.y;
	pPositions->p1.z -= addSiz.z;

	pPositions->p2.x -= addSiz.x;
	pPositions->p2.y += addSiz.y;
	pPositions->p2.z -= addSiz.z;

	pPositions->p3.x -= addSiz.x;
	pPositions->p3.y -= addSiz.y;
	pPositions->p3.z += addSiz.z;

	pPositions->p4.x += addSiz.x;
	pPositions->p4.y += addSiz.y;
	pPositions->p4.z -= addSiz.z;

	pPositions->p5.x -= addSiz.x;
	pPositions->p5.y += addSiz.y;
	pPositions->p5.z += addSiz.z;

	pPositions->p6.x += addSiz.x;
	pPositions->p6.y -= addSiz.y;
	pPositions->p6.z += addSiz.z;
}

/// <summary>
/// ���_���W�Q�̈ړ�
/// </summary>
/// <param name="pPositions">�ړ�������ڕW</param>
/// <param name="move">�ړ���</param>
void ColliderBace::MovePositions(Positions* pPositions, const DirectX::SimpleMath::Vector3& move)
{
	if (!pPositions)
		return;

	pPositions->max += move;
	pPositions->min += move;
	pPositions->p1  += move;
	pPositions->p2  += move;
	pPositions->p3  += move;
	pPositions->p4  += move;
	pPositions->p5  += move;
	pPositions->p6  += move;
}
