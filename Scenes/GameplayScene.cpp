/**
 * @file   GameplayScene.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "GameplayScene.h"

// 使用するオブジェクト
#include "../Objects/Player.h"
#include "../Objects/MapGenerator.h"
#include "../Objects/Enemy.h"

#include "../Managers/SceneManager.h"
#include "../Components/Transform.h"

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

    // デバッグフォントの作成
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // グリッド床の作成
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States );
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

	// カメラの作成
    m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(0.f, 10.f, 5.f));

    // プレイヤーの作成
    AddObject("Player", std::make_unique<Player>(this));

    // プレイヤーのトランスフォームの取得
    Transform* playerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

    // カメラの注視点をプレイヤーに設定
    m_Camera->SetTargetPositionPtr(playerTransform);

    // MapGeneratorの作成
    AddObject("MapGenerator", std::make_unique<MapGenerator>(this));

    // エネミーの作成
    AddObject("Enemy", std::make_unique<Enemy>(this, playerTransform->GetPosition() + SimpleMath::Vector3(1.f, 0.f, 0.f)));
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
    m_debugFont.reset();
    m_gridFloor.reset();
    m_Camera.reset();
}