/**
 * @file   GameplayScene.cpp
 *
 * @brief  �Q�[���v���C�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "GameplayScene.h"

 // �O���錾
#include "Camera.h"

// �g�p����I�u�W�F�N�g
#include "../Objects/Player.h"
#include "../Objects/MapGenerator.h"
#include "../Objects/Enemy.h"

#include "../Managers/SceneManager.h"
#include "../Components/Transform.h"
#include "DDSTextureLoader.h"

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
) noexcept(false):
    SceneBace(sceneManager, pDeviceResources, pProj, pStates),
    mp_timer{ pTimer }
{
    auto device = mp_DeviceResources->GetD3DDevice();
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // Skybox�̍쐬

    m_sky = GeometricPrimitive::CreateGeoSphere(context, 1.0f, 3,
        false /*invert for bein inside the shape*/);

    m_effect = std::make_unique<SkyboxEffect>(device);

    m_sky->CreateInputLayout(m_effect.get(),
        m_skyInputLayout.ReleaseAndGetAddressOf());

    DX::ThrowIfFailed(
        CreateDDSTextureFromFile(device, L"Resources\\Textures\\lobbycube.dds",
            nullptr, m_cubemap.ReleaseAndGetAddressOf()));

    m_effect->SetTexture(m_cubemap.Get());

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
/// Destructor
/// </summary>
GameplayScene::~GameplayScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void GameplayScene::Initialize()
{
    //int width  = mp_DeviceResources->GetOutputSize().right  - mp_DeviceResources->GetOutputSize().left;
    //int height = mp_DeviceResources->GetOutputSize().bottom - mp_DeviceResources->GetOutputSize().top;

    m_effect->SetProjection(*mp_Proj);

	// �J�����̍쐬
    m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(0.f, 13.f, 3.f));
	//m_DebugCamera = std::make_unique<Imase::DebugCamera>(width, height);

    // �v���C���[�̍쐬
    AddObject("Player", std::make_unique<Player>(this, "Player"));

    // �v���C���[�̃g�����X�t�H�[���̎擾
    Transform* playerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

    // �J�����̒����_���v���C���[�ɐݒ�
    m_Camera->SetTargetPositionPtr(playerTransform);

    // MapGenerator�̍쐬
    AddObject("MapGenerator", std::make_unique<MapGenerator>(this, "MapGenerator"));

    // �G�l�~�[�̍쐬
    AddObject("Enemy", std::make_unique<Enemy>(this, "Enemy", playerTransform->GetPosition() + SimpleMath::Vector3(1.f, 0.f, 0.f)));
}

/// <summary>
/// �X�V����
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // �x�����p
    elapsedTime;

    // �J�����̍X�V����
    m_Camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�J��������r���[�s����擾����
    SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

    // Skybox�̕`�揈��
    m_effect->SetView(view);
    m_sky->Draw(m_effect.get(), m_skyInputLayout.Get());

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

    // Player�̍��W���擾
    SimpleMath::Vector3 playerPosition = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"))->GetPosition();

    // Player�̍��W��\��
    m_debugFont->AddString(200, 0, Colors::Red, L"Player=(%f, %f, %f)", playerPosition.x, playerPosition.y, playerPosition.z);

    // �f�o�b�O�t�H���g�̕`��
    m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void GameplayScene::Finalize()
{
    m_Camera.reset();

    m_sky.reset();
    m_effect.reset();
    m_skyInputLayout.Reset();
    m_cubemap.Reset();
}