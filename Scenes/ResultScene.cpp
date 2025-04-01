/**
 * @file   ResultScene.cpp
 *
 * @brief  リザルトシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "ResultScene.h"

#include "../Managers/SceneManager.h"

using namespace std;
using namespace DirectX;

// ボタンが押せるようになるまでの時間
static constexpr float ButtonEnableTime = 1.0f;

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
	mp_timer{ pTimer },
	m_buttonEnableTime{ 0.f }
{
}

/// <summary>
/// Destructor
/// </summary>
ResultScene::~ResultScene() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	// カメラの作成
	m_Camera = std::make_unique<Camera>(SimpleMath::Vector3(5.f, 0.f, 0.f));

	// ボタンが押せるようになるまでの時間の初期化
	m_buttonEnableTime = ButtonEnableTime;

#if defined(_DEBUG)
	// デバッグ時の追加初期化処理
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// デバッグフォントの作成
	m_debugFont = std::make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// グリッド床の作成
	m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間[s]</param>
void ResultScene::Update(const float elapsedTime)
{
	// 時間の経過
	m_buttonEnableTime -= elapsedTime;

	// カメラの更新処理
	m_Camera->Update();

	// もし、ボタンが押せるようになるまでの時間が0より大きかった際の早期リターン
	if (m_buttonEnableTime > 0.f) return;

	// ボタンが押せるようになるまでの時間を0にする
	m_buttonEnableTime = 0.f;

	// キーボードの取得
	Keyboard::State kb = Keyboard::Get().GetState();

	// もし、何かしらのアクションキーが押されていて、ボタンが押されるようになっていたらタイトルシーンに遷移
	if ((kb.C || kb.I || kb.X || kb.K || kb.Z || kb.J || kb.V || kb.L) && m_buttonEnableTime <= 0.f)
		// シーンの遷移
		ChangeScene("Title");
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Render()
{
	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// オブジェクトの描画処理
	mp_SceneManager->GetObjectManagerPtr()->Render(view);

#if defined(_DEBUG)
	/*デバッグ表示*/
	// コンテキストの取得
	auto context = mp_DeviceResources->GetD3DDeviceContext();

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

#if defined(_DEBUG)
	/*デバッグ時の追加終了処理*/
	m_debugFont.reset();
	m_gridFloor.reset();
#endif
}
