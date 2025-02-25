/**
 * @file   GameplayScene.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
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

    // デバッグフォントの作成
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // グリッド床の作成
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States );

    // プレイヤーの作成
    m_player = std::make_unique<Player>(mp_DeviceResources, mp_Proj, mp_States);

    // ToDo : トランスフォームの実装
    // ToDo : オブジェクトマネージャの導入
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

    // プレイヤーの初期化処理
    m_player->Initialize();
    m_player->GetTransformPointer()->SetScale(0.35f);
}

/// <summary>
/// 更新処理
/// </summary>
void GameplayScene::Update(const float elapsedTime)
{
    // デバッグカメラの更新
    m_debugCamera->Update();

    // プレイヤーの更新処理
    m_player->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
void GameplayScene::Render()
{
    auto context = mp_DeviceResources->GetD3DDeviceContext();

    // デバッグカメラからビュー行列を取得する
    SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();

    // プレイヤーの描画処理
    m_player->Draw(view);

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
    // オブジェクトの終了処理
    m_player->Finalize();
    m_player.reset();

    m_debugFont.reset();
    m_gridFloor.reset();
    m_debugCamera.reset();
}