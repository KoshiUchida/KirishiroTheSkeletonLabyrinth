/**
 * @file   GameplayScene.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
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

    // デバッグフォントの作成
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // グリッド床の作成
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States );

    // モデルの読み込み
    EffectFactory fx(device);
    m_model = Model::CreateFromSDKMESH(
        device, L"Resources\\Models\\Kirishiro.sdkmesh", fx);
}

/// <summary>
/// Destructor
/// </summary>
GameplayScene::~GameplayScene() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void GameplayScene::Initialize()
{
    float width  = static_cast<float>(mp_DeviceResources->GetOutputSize().right  - mp_DeviceResources->GetOutputSize().left);
    float height = static_cast<float>(mp_DeviceResources->GetOutputSize().bottom - mp_DeviceResources->GetOutputSize().top );

	// デバッグカメラの作成
    m_debugCamera = std::make_unique<Imase::DebugCamera>(width, height);
}

/// <summary>
/// 更新処理
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // デバッグカメラの更新
    m_debugCamera->Update();


    // キーボードの入力を取得
    auto kd = Keyboard::Get().GetState();

    float rotateSpeed = 75.f;

    //// 速度ベクトル
    //SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

    //// Y軸で回転する行列を作成する
    //SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotateY);
    //v = SimpleMath::Vector3::Transform(v, rotY);

    // 左キーが押されているか
    if (kd.Left)
    {
        m_position.x -= 3.0f * elapsedTime;
    }

    // 右キーが押されているか
    if (kd.Right)
    {
        m_position.x += 3.0f * elapsedTime;
    }

    // 上キーが押されているか  
    if (kd.Up)
    {
        m_position.z -= 3.0f * elapsedTime;
    }

    // 下キーが押されているか
    if (kd.Down)
    {
        m_position.z += 3.0f * elapsedTime;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // デバッグカメラからビュー行列を取得する
    SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();

    // ワールド行列
    SimpleMath::Matrix world;

    //m_position.z += 0.01f;

    // 平行移動する行列を作成する
    SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_position);

    //m_rotateY = XMConvertToRadians(90.0f);

    // Y軸で回転する行列を作成する
    SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotateY);

    // ２売に拡大する
    SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(0.5f);

    world = rotY * trans * scale;

    // モデルの描画
    m_model->Draw(context, *mp_States, world, view, *mp_Proj);

    // グリッドの床の描画
    m_gridFloor->Render(context, view, *mp_Proj);

    // FPSを取得する
    uint32_t fps = mp_timer->GetFramesPerSecond();

    // FPSの表示
    m_debugFont->AddString(0, 0, Colors::White, L"FPS=%d", fps);

    // デバッグフォントの描画
    m_debugFont->Render(mp_States);
}

/// <summary>
/// 終了処理
/// </summary>
void GameplayScene::Finalize()
{
}