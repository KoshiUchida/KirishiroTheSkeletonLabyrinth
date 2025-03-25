/**
 * @file   ResultScene.cpp
 *
 * @brief  リザルトシーンのソースファイル
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

	// デバッグフォントの作成
	m_debugFont = std::make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// グリッド床の作成
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
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	// カメラの作成
	m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(5.f, 0.f, 0.f));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間[s]</param>
void ResultScene::Update(const float elapsedTime)
{
	// 警告回避用
	elapsedTime;

	// カメラの更新処理
	m_Camera->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// オブジェクトの描画処理
	mp_SceneManager->GetObjectManagerPtr()->Render(view);

#if defined(_DEBUG)
	/*デバッグ表示*/

	// グリッドの床の描画
	m_gridFloor->Render(context, view, *mp_Proj);

	// 現在のシーン名
	m_debugFont->AddString(0, 0, Colors::Red, L"Scene:Result");

	// FPSを取得する
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPSの表示
	m_debugFont->AddString(0, 100, Colors::White, L"FPS=%d", fps);

	// デバッグフォントの描画
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void ResultScene::Finalize()
{
	m_Camera.reset();
}
