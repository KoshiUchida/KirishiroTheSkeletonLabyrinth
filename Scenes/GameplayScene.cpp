/**
 * @file   GameplayScene.cpp
 *
 * @brief  �Q�[���v���C�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "GameplayScene.h"
#include "../Objects/Player.h"
#include "../Objects/MapGenerator.h"
#include "../Managers/SceneManager.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
GameplayScene::GameplayScene
(
                   SceneManager* sceneManager,
            DX::DeviceResources* pDeviceResources,
    DirectX::SimpleMath::Matrix* pProj,
          DirectX::CommonStates* pStates,
                  DX::StepTimer* pTimer
) noexcept(false)
	: SceneBace(sceneManager, pDeviceResources, pProj, pStates)
    , mp_timer{ pTimer }
{
    auto device = mp_DeviceResources->GetD3DDevice();
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�t�H���g�̍쐬
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // �O���b�h���̍쐬
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States );
}

/// <summary>
/// Destructor
/// </summary>
GameplayScene::~GameplayScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void GameplayScene::Initialize()
{
    int width  = mp_DeviceResources->GetOutputSize().right  - mp_DeviceResources->GetOutputSize().left;
    int height = mp_DeviceResources->GetOutputSize().bottom - mp_DeviceResources->GetOutputSize().top;

	// �J�����̍쐬
    m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(1.f, 1.f, 1.f));

    // �v���C���[�̍쐬
    AddObject("Player", std::make_unique<Player>(this));

    // MapGenerator�̍쐬
    AddObject("MapGenerator", std::make_unique<MapGenerator>(this));
}

/// <summary>
/// �X�V����
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // �x�����p
    elapsedTime;
}

/// <summary>
/// �`�揈��
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�J��������r���[�s����擾����
    SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

    // �I�u�W�F�N�g�̕`�揈��
    mp_SceneManager->GetObjectManagerPtr()->Render(view);

    /*�f�o�b�O�\��*/
#if defined(_DEBUG)
    // �O���b�h�̏��̕`��
    m_gridFloor->Render(context, view, *mp_Proj);

    // FPS���擾����
    uint32_t fps = mp_timer->GetFramesPerSecond();

    // FPS�̕\��
    m_debugFont->AddString(0, 0, Colors::White, L"FPS=%d", fps);

    // �f�o�b�O�t�H���g�̕`��
    m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void GameplayScene::Finalize()
{
    m_debugFont.reset();
    m_gridFloor.reset();
    m_Camera.reset();
}