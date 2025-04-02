/**
 * @file   Renderer3DWithAnimation.cpp
 *
 * @brief  �A�j���[�V�����t��3���������_���[�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "Renderer3DWithAnimation.h"

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
Renderer3DWithAnimation::Renderer3DWithAnimation(
	SceneBace* pScene,
	std::string name,
	Transform* pTransform,
	const wchar_t* modelPath) noexcept :
	ComponentsBace(ComponentsBace::Tags::UAndR, name),
	mp_States         { pScene->GetCommonStatesPointer()},
	mp_DeviceResources{ pScene->GetDeviceResourcesPointer() },
	mp_Proj           { pScene->GetProjPointer() },
	mp_Transform      { pTransform }
{
	// �f�o�C�X�̎擾
	auto device = mp_DeviceResources->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Textures");

	// ���f���̓ǂݍ���
	m_Model = Model::CreateFromSDKMESH(device, modelPath,
		fx,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);

	m_drawBones = ModelBone::MakeArray(m_Model->bones.size());

	m_Model->UpdateEffects([&](IEffect* effect)
		{
			auto skin = dynamic_cast<SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		}
	);
}

/// <summary>
/// Destructor
/// </summary>
Renderer3DWithAnimation::~Renderer3DWithAnimation() noexcept
{
	m_Animation.Release();

	m_Model.reset();
}

/// <summary>
/// �Đ�����A�j���[�V�����̐ݒ�֐�
/// </summary>
void Renderer3DWithAnimation::SetAnimation(const wchar_t* animationPath)
{
	DX::ThrowIfFailed(
		m_Animation.Load(animationPath)
	);

	m_Animation.Bind(*m_Model);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapseTime">�o�ߎ���[s]</param>
void Renderer3DWithAnimation::Update(float elapseTime)
{
	// �A�j���[�V�����̍X�V����
	m_Animation.Update(elapseTime);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
void Renderer3DWithAnimation::Draw(const DirectX::SimpleMath::Matrix& view)
{
	// �R���e�L�X�g�̎擾
	auto context = mp_DeviceResources->GetD3DDeviceContext();
	size_t nbones = m_Model->bones.size();

	// �A�j���[�V�����̓K�p
	m_Animation.Apply(*m_Model, nbones, m_drawBones.get());

	// ���[���h�s��
	SimpleMath::Matrix world;

	// ���s�ړ�����s����쐬����
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X���ŉ�]����s����쐬����
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y���ŉ�]����s����쐬����
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z���ŉ�]����s����쐬����
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationZ(mp_Transform->GetRotateZ());

	// �g�傷��s����쐬����
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ���[���h�s��֓���
	world = scale * rotZ * rotY * rotX * trans;

	// ���f���̕`��
	m_Model->DrawSkinned(context, *mp_States, nbones, m_drawBones.get(),
		world, view, *mp_Proj);
}
