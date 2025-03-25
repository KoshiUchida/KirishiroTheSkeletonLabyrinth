/**
 * @file   LogoScene.cpp
 *
 * @brief  ���S�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "LogoScene.h"

#include "DDSTextureLoader.h"

// �O���錾
#include "Camera.h"

using namespace std;
using namespace DirectX;

// ���S�̃t�F�[�h�C������
static constexpr float LogoFadeInTime{ 3.0f };

// ���S�̃A�C�h������
static constexpr float LogoIdolTime{ 1.5f };

// ���S�̃t�F�[�h�A�E�g����
static constexpr float LogoFadeOutTime{ 1.5f };

/// <summary>
/// Constructor
/// </summary>
LogoScene::LogoScene(SceneManager* sceneManager, DX::DeviceResources* pDeviceResources, DirectX::SimpleMath::Matrix* pProj, DirectX::CommonStates* pStates, DX::StepTimer* pTimer) noexcept(false):
	SceneBace(sceneManager, pDeviceResources, pProj, pStates),
	mp_timer   { pTimer },
	m_Time     { 0.f },
	m_LogoAlpha{ 0.f }
{
}

/// <summary>
/// Destructor
/// </summary>
LogoScene::~LogoScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void LogoScene::Initialize()
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �o�ߎ��Ԃ̏�����
	m_Time = 0.f;

	// �J�����̍쐬
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(3.f, 0.f, 0.f));

	// �X�v���C�g�o�b�`�̍쐬
	m_SpriteBatch = make_unique<SpriteBatch>(context);

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	
	// ���S�̃e�N�X�`���̓ǂݍ���
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Resources\\Textures\\Logo.dds",
			resource.GetAddressOf(), m_texture_Logo.ReleaseAndGetAddressOf()));

	// ���S�̃e�N�X�`���̃T�C�Y���擾
	Microsoft::WRL::ComPtr<ID3D11Texture2D> logo;
	DX::ThrowIfFailed(resource.As(&logo));

	CD3D11_TEXTURE2D_DESC logoDesc;
	logo->GetDesc(&logoDesc);

	// ���S�̃e�N�X�`���̃I���W���̐ݒ�
	m_LogoOrigin = SimpleMath::Vector2(logoDesc.Width / 2.f, logoDesc.Height / 2.f);

	// ���S�̃e�N�X�`���̍��W�̐ݒ�
	auto size = mp_DeviceResources->GetOutputSize();
	m_LogoPos = SimpleMath::Vector2(size.right / 2.f, size.bottom / 2.f);

	// ���S�̃A���t�@�l�̏�����
	m_LogoAlpha = 0.f;

#if defined(_DEBUG)
	/*�f�o�b�O���̒ǉ�����������*/
	// �f�o�b�O�t�H���g�̍쐬
	m_debugFont = std::make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// �O���b�h���̍쐬
	m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States);

#endif
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���[s]</param>
void LogoScene::Update(const float elapsedTime)
{
	// �o�ߎ��Ԃ̉��Z
	m_Time += elapsedTime;

	// ���S�̃A���t�@�l�̍X�V
	if (m_Time < LogoFadeInTime)
	{
		// ���S�̃t�F�[�h�C��
		m_LogoAlpha = m_Time / LogoFadeInTime;
	}
	else if (m_Time < LogoFadeInTime + LogoIdolTime)
	{
		// ���S�̃A�C�h��
		m_LogoAlpha = 1.f;
	}
	else if (m_Time < LogoFadeInTime + LogoIdolTime + LogoFadeOutTime)
	{
		// ���S�̃t�F�[�h�A�E�g
		m_LogoAlpha = 1.f - (m_Time - LogoFadeInTime - LogoIdolTime) / LogoFadeOutTime;
	}
	else
	{
		// �^�C�g���V�[���ɑJ��
		ChangeScene("Title");
	}

	// �L�[�{�[�h�̎擾
	Keyboard::State kd = Keyboard::Get().GetState();

	// �����AZ�L�[��������Ă�����^�C�g���V�[���ɑJ��
	if (kd.Z)
		// �V�[���̑J��
		ChangeScene("Title");

	// �J�����̍X�V
	//m_Camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void LogoScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �f�o�b�O�J��������r���[�s����擾����
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// ���S�̕`��
	m_SpriteBatch->Begin();

	// ���S�̃T�C�Y
	static constexpr float logoSize = 0.15f;

	m_SpriteBatch->Draw(m_texture_Logo.Get(), m_LogoPos, nullptr,
		SimpleMath::Color(1.f, 1.f, 1.f, m_LogoAlpha), 0.f, m_LogoOrigin,
		logoSize
	);

	m_SpriteBatch->End();

#if defined(_DEBUG)
	/*�f�o�b�O�\��*/
	// �O���b�h�̏��̕`��
	m_gridFloor->Render(context, view, *mp_Proj);

	// �V�[���̖��O�̕\��
	m_debugFont->AddString(0, 0, Colors::White, L"Scene:LogoScene");

	// FPS���擾����
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPS�̕\��
	m_debugFont->AddString(0, 50, Colors::White, L"FPS=%d", fps);

	// �f�o�b�O�t�H���g�̕`��
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void LogoScene::Finalize()
{
	m_Camera     .reset();
	m_debugFont  .reset();
	m_gridFloor  .reset();
	m_SpriteBatch.reset();

	m_texture_Logo.Reset();
}
