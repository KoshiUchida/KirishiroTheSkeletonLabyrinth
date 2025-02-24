/**
 * @file   GameplayScene.cpp
 *
 * @brief  �Q�[���v���C�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/10
 */

#include "pch.h"
#include "GameplayScene.h"

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
	, m_rotateY(90.0f)
{
    auto device = mp_DeviceResources->GetD3DDevice();
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�t�H���g�̍쐬
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // �O���b�h���̍쐬
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States );

    // ���f���̓ǂݍ���
    EffectFactory fx(device);
    m_model = Model::CreateFromSDKMESH(
        device, L"Resources\\Models\\Kirishiro.sdkmesh", fx);
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
}

/// <summary>
/// �X�V����
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // �f�o�b�O�J�����̍X�V
    m_debugCamera->Update();


    // �L�[�{�[�h�̓��͂��擾
    auto kd = Keyboard::Get().GetState();

    float rotateSpeed = 75.f;

    //// ���x�x�N�g��
    //SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

    //// Y���ŉ�]����s����쐬����
    //SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotateY);
    //v = SimpleMath::Vector3::Transform(v, rotY);

    // ���L�[��������Ă��邩
    if (kd.Left)
    {
        m_position.x -= 3.0f * elapsedTime;
    }

    // �E�L�[��������Ă��邩
    if (kd.Right)
    {
        m_position.x += 3.0f * elapsedTime;
    }

    // ��L�[��������Ă��邩  
    if (kd.Up)
    {
        m_position.z -= 3.0f * elapsedTime;
    }

    // ���L�[��������Ă��邩
    if (kd.Down)
    {
        m_position.z += 3.0f * elapsedTime;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // �f�o�b�O�J��������r���[�s����擾����
    SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();

    // ���[���h�s��
    SimpleMath::Matrix world;

    //m_position.z += 0.01f;

    // ���s�ړ�����s����쐬����
    SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_position);

    //m_rotateY = XMConvertToRadians(90.0f);

    // Y���ŉ�]����s����쐬����
    SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotateY);

    // �Q���Ɋg�傷��
    SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(0.5f);

    world = rotY * trans * scale;

    // ���f���̕`��
    m_model->Draw(context, *mp_States, world, view, *mp_Proj);

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
}