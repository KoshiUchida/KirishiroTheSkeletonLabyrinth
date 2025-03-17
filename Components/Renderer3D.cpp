/**
 * @file   Renderer3D.cpp
 *
 * @brief  ���f���`��R���|�[�l���g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#include "pch.h"
#include "Renderer3D.h"

#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

Renderer3D::Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false)
	: RendererBace("Renderer3D", pScene->GetCommonStatesPointer())
	, mp_Transform{ pTransform }
	, mp_DeviceResources{ pScene->GetDeviceResourcesPointer() }
	, mp_Proj{ pScene->GetProjPointer() }
{
	// ���f���̓ǂݍ���
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
		device, modelPath, fx);
}

Renderer3D::~Renderer3D() noexcept
{
	m_Model.reset();
}

void Renderer3D::Draw(const DirectX::SimpleMath::Matrix& view)
{
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
	world = scale * rotZ * rotY * rotX  * trans;

	// ���f���̕`��
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}
