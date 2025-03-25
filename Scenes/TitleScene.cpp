/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "TitleScene.h"

 // �O���錾
#include "Camera.h"

using namespace std;
using namespace DirectX;

// �{�^����������悤�ɂȂ�܂ł̎���
static constexpr float ButtonEnableTime = 1.0f;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene(SceneManager* sceneManager, DX::DeviceResources* pDeviceResources, DirectX::SimpleMath::Matrix* pProj, DirectX::CommonStates* pStates, DX::StepTimer* pTimer) noexcept(false):
	SceneBace(sceneManager, pDeviceResources, pProj, pStates),
	mp_timer{ pTimer },
	m_buttonEnableTime{ ButtonEnableTime }
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

#if defined(_DEBUG)
	/*�f�o�b�O���̒ǉ�����������*/
	// �f�o�b�O�t�H���g�̍쐬
	m_debugFont = make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// �O���b�h���̍쐬
	m_gridFloor = make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(3.0f, 0.0f, 0.0f));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���[s]</param>
void TitleScene::Update(const float elapsedTime)
{
	// �J�����X�V
	m_Camera->Update();

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ����炷
	m_buttonEnableTime -= elapsedTime;

	// �����A�{�^����������悤�ɂȂ�܂ł̎��Ԃ�0���傫�������ۂ̑������^�[��
	if (m_buttonEnableTime > 0.f) return;

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ�0�ɂ���
	m_buttonEnableTime = 0.f;

	// �L�[�{�[�h�̎擾
	Keyboard::State kd = Keyboard::Get().GetState();

	// �����AZ�L�[��������Ă��āA�{�^�����������悤�ɂȂ��Ă�����Q�[���v���C�V�[���ɑJ��
	if (kd.Z && m_buttonEnableTime <= 0.f)
		// �V�[���̑J��
		ChangeScene("Gameplay");
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �f�o�b�O�J��������r���[�s����擾����
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	/*�f�o�b�O�\��*/
#if defined(_DEBUG)
	// �O���b�h�̏��̕`��
	m_gridFloor->Render(context, view, *mp_Proj);

	// �V�[�����̕\��
	m_debugFont->AddString(0, 0, Colors::White, L"Scene=Title");

	// FPS���擾����
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPS�̕\��
	m_debugFont->AddString(0, 15, Colors::White, L"FPS=%d", fps);

	// �f�o�b�O�t�H���g�̕`��
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	m_Camera.reset();
}
