/**
 * @file   GameplayScene.cpp
 *
 * @brief  �Q�[���v���C�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#include "pch.h"
#include "GameplayScene.h"
#include "../Objects/Player.h"

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

    // �v���C���[�̍쐬
    m_player = std::make_unique<Player>(mp_DeviceResources, mp_Proj, mp_States);

    // ToDo : �g�����X�t�H�[���̎���
    // ToDo : �I�u�W�F�N�g�}�l�[�W���̓���
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
    float width  = static_cast<float>(mp_DeviceResources->GetOutputSize().right  - mp_DeviceResources->GetOutputSize().left);
    float height = static_cast<float>(mp_DeviceResources->GetOutputSize().bottom - mp_DeviceResources->GetOutputSize().top );

	// �f�o�b�O�J�����̍쐬
    m_debugCamera = std::make_unique<Imase::DebugCamera>(width, height);

    // �v���C���[�̏���������
    m_player->Initialize();
    m_player->GetTransformPointer()->SetScale(0.35f);
}

/// <summary>
/// �X�V����
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // �f�o�b�O�J�����̍X�V
    m_debugCamera->Update();

    // �v���C���[�̍X�V����
    m_player->Update(elapsedTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�J��������r���[�s����擾����
    SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();

    // �v���C���[�̕`�揈��
    m_player->Draw(view);

    // �O���b�h�̏��̕`��
    m_gridFloor->Render(context, view, *mp_Proj);

    // FPS���擾����
    uint32_t fps = mp_timer->GetFramesPerSecond();

    // FPS�̕\��
    m_debugFont->AddString(0, 0, Colors::White, L"FPS=%d", fps);

    // �f�o�b�O�t�H���g�̕`��
    m_debugFont->Render(mp_States);
}

/// <summary>
/// �I������
/// </summary>
void GameplayScene::Finalize()
{
    // �I�u�W�F�N�g�̏I������
    m_player->Finalize();
    m_player.reset();

    m_debugFont.reset();
    m_gridFloor.reset();
    m_debugCamera.reset();
}