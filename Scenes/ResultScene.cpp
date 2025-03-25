/**
 * @file   ResultScene.cpp
 *
 * @brief  ���U���g�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "ResultScene.h"

#include "../Managers/SceneManager.h"

using namespace std;
using namespace DirectX;

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
	mp_timer{ pTimer }
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �f�o�b�O�t�H���g�̍쐬
	m_debugFont = std::make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// �O���b�h���̍쐬
	m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States);
}

/// <summary>
/// Destructor
/// </summary>
ResultScene::~ResultScene() noexcept
{
	mp_timer = nullptr;

	m_debugFont.reset();
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	// �J�����̍쐬
	m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(5.f, 0.f, 0.f));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���[s]</param>
void ResultScene::Update(const float elapsedTime)
{
	// �x�����p
	elapsedTime;

	// �J�����̍X�V����
	m_Camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// �f�o�b�O�J��������r���[�s����擾����
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// �I�u�W�F�N�g�̕`�揈��
	mp_SceneManager->GetObjectManagerPtr()->Render(view);

#if defined(_DEBUG)
	/*�f�o�b�O�\��*/

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
}
