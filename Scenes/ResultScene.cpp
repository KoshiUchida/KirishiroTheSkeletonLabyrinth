/**
 * @file   ResultScene.cpp
 *
 * @brief  ���U���g�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "ResultScene.h"

#include "../Managers/SceneManager.h"

using namespace std;
using namespace DirectX;

// �{�^����������悤�ɂȂ�܂ł̎���
static constexpr float ButtonEnableTime = 1.0f;

/// <summary>
/// Constructor
/// </summary>
ResultScene::ResultScene(
	               SceneManager* sceneManager,
	        DX::DeviceResources* pDeviceResources,
	DirectX::SimpleMath::Matrix* pProj,
	      DirectX::CommonStates* pStates,
	              DX::StepTimer* pTimer
) noexcept(false):
	SceneBace(
		sceneManager,
		pDeviceResources,
		pProj,
		pStates
	),
	mp_timer{ pTimer },
	m_buttonEnableTime{ 0.f }
{
}

/// <summary>
/// Destructor
/// </summary>
ResultScene::~ResultScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	// �J�����̍쐬
	m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(5.f, 0.f, 0.f));

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ̏�����
	m_buttonEnableTime = ButtonEnableTime;

#if defined(_DEBUG)
	// �f�o�b�O���̒ǉ�����������
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

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
void ResultScene::Update(const float elapsedTime)
{
	// ���Ԃ̌o��
	m_buttonEnableTime -= elapsedTime;

	// �J�����̍X�V����
	m_Camera->Update();

	// �����A�{�^����������悤�ɂȂ�܂ł̎��Ԃ�0���傫�������ۂ̑������^�[��
	if (m_buttonEnableTime > 0.f) return;

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ�0�ɂ���
	m_buttonEnableTime = 0.f;

	// �L�[�{�[�h�̎擾
	Keyboard::State kb = Keyboard::Get().GetState();

	// �����A��������̃A�N�V�����L�[��������Ă��āA�{�^�����������悤�ɂȂ��Ă�����^�C�g���V�[���ɑJ��
	if ((kb.C || kb.I || kb.X || kb.K || kb.Z || kb.J || kb.V || kb.L) && m_buttonEnableTime <= 0.f)
		// �V�[���̑J��
		ChangeScene("Title");
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Render()
{
	// �f�o�b�O�J��������r���[�s����擾����
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// �I�u�W�F�N�g�̕`�揈��
	mp_SceneManager->GetObjectManagerPtr()->Render(view);

#if defined(_DEBUG)
	/*�f�o�b�O�\��*/
	// �R���e�L�X�g�̎擾
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �O���b�h�̏��̕`��
	m_gridFloor->Render(context, view, *mp_Proj);

	// ���݂̃V�[����
	m_debugFont->AddString(0, 0, Colors::Red, L"Scene:Result");

	// FPS���擾����
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPS�̕\��
	m_debugFont->AddString(0, 100, Colors::White, L"FPS=%d", fps);

	// �f�o�b�O�t�H���g�̕`��
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{
	m_Camera.reset();

#if defined(_DEBUG)
	/*�f�o�b�O���̒ǉ��I������*/
	m_debugFont.reset();
	m_gridFloor.reset();
#endif
}
