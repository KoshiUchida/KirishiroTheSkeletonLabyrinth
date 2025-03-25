/**
 * @file   GameplayScene.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "GameplayScene.h"

 // 前方宣言
#include "Camera.h"

// 使用するオブジェクト
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

    // Skyboxの作成

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
    /*デバッグ時の追加初期化処理*/
    // デバッグフォントの作成
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // グリッド床の作成
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
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
    //int width  = mp_DeviceResources->GetOutputSize().right  - mp_DeviceResources->GetOutputSize().left;
    //int height = mp_DeviceResources->GetOutputSize().bottom - mp_DeviceResources->GetOutputSize().top;

    m_effect->SetProjection(*mp_Proj);

	// カメラの作成
    m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(0.f, 13.f, 3.f));
	//m_DebugCamera = std::make_unique<Imase::DebugCamera>(width, height);

    // プレイヤーの作成
    AddObject("Player", std::make_unique<Player>(this, "Player"));

    // プレイヤーのトランスフォームの取得
    Transform* playerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

    // カメラの注視点をプレイヤーに設定
    m_Camera->SetTargetPositionPtr(playerTransform);

    // MapGeneratorの作成
    AddObject("MapGenerator", std::make_unique<MapGenerator>(this, "MapGenerator"));

    // エネミーの作成
    AddObject("Enemy", std::make_unique<Enemy>(this, "Enemy", playerTransform->GetPosition() + SimpleMath::Vector3(1.f, 0.f, 0.f)));
}

/// <summary>
/// 更新処理
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // 警告回避用
    elapsedTime;

    // カメラの更新処理
    m_Camera->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // デバッグカメラからビュー行列を取得する
    SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

    // Skyboxの描画処理
    m_effect->SetView(view);
    m_sky->Draw(m_effect.get(), m_skyInputLayout.Get());

    // オブジェクトの描画処理
    mp_SceneManager->GetObjectManagerPtr()->Render(view);

    /*デバッグ表示*/
#if defined(_DEBUG)
    // グリッドの床の描画
    m_gridFloor->Render(context, view, *mp_Proj);

    // FPSを取得する
    uint32_t fps = mp_timer->GetFramesPerSecond();

    // FPSの表示
    m_debugFont->AddString(0, 0, Colors::White, L"FPS=%d", fps);

    // Playerの座標を取得
    SimpleMath::Vector3 playerPosition = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"))->GetPosition();

    // Playerの座標を表示
    m_debugFont->AddString(200, 0, Colors::Red, L"Player=(%f, %f, %f)", playerPosition.x, playerPosition.y, playerPosition.z);

    // デバッグフォントの描画
    m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void GameplayScene::Finalize()
{
    m_Camera.reset();

    m_sky.reset();
    m_effect.reset();
    m_skyInputLayout.Reset();
    m_cubemap.Reset();
}