/**
 * @file   Renderer2D.cpp
 *
 * @brief  �Q���������_���[�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "Renderer2D.h"

#include "DDSTextureLoader.h"

// �O���錾
#include "../Scenes/SceneBace.h"
#include "Transform2D.h"

using namespace std;
using namespace DirectX;

Renderer2D::Renderer2D(SceneBace* pScene, const std::string& name, Transform2D* pTransform, const wchar_t* modelPath) noexcept :
	RendererBace(name, pScene->GetCommonStatesPointer()),
	mp_Transform{ pTransform },
	mp_DeviceResources{ pScene->GetDeviceResourcesPointer() },
	m_Alpha{ 1.f },
	m_Offset{ DirectX::SimpleMath::Vector2::Zero }
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`�̍쐬
	m_SpriteBatch = make_unique<SpriteBatch>(context);

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;

	// �e�N�X�`���̓ǂݍ���
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, modelPath,
			resource.GetAddressOf(), m_Texture.ReleaseAndGetAddressOf()));

	// �e�N�X�`���̃T�C�Y���擾
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	DX::ThrowIfFailed(resource.As(&texture));

	CD3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	// �e�N�X�`���̃I���W���̐ݒ�
	m_Origin = SimpleMath::Vector2(textureDesc.Width / 2.f, textureDesc.Height / 2.f);
}

Renderer2D::~Renderer2D() noexcept
{
	m_Texture.Reset();

	m_SpriteBatch.reset();
}

void Renderer2D::Draw(const DirectX::SimpleMath::Matrix& view)
{
	// �x�����p
	view;

	// �`��J�n
	m_SpriteBatch->Begin(SpriteSortMode_Deferred, mp_States->NonPremultiplied());

	// �e�N�X�`���̕`��
	m_SpriteBatch->Draw(m_Texture.Get(), mp_Transform->GetPosition(mp_DeviceResources) + m_Offset, nullptr,
		SimpleMath::Color(1.f, 1.f, 1.f, m_Alpha), mp_Transform->GetRotate(), m_Origin,
		mp_Transform->GetScale()
	);

	// �`��I��
	m_SpriteBatch->End();
}

void Renderer2D::SetOrigin(DirectX::SimpleMath::Vector2 origin)
{
	m_Origin = origin;
}

void Renderer2D::SetAlpha(float alpha)
{
	m_Alpha = alpha;
}

void Renderer2D::SetOffset(DirectX::SimpleMath::Vector2 offset)
{
	m_Offset = offset;
}
