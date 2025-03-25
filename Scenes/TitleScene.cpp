/**
 * @file   TitleScene.h
 *
 * @brief  タイトルシーンのヘッダファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "TitleScene.h"

 // 前方宣言
#include "Camera.h"

using namespace std;
using namespace DirectX;

// ボタンが押せるようになるまでの時間
static constexpr float ButtonEnableTime = 1.0f;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene(SceneManager* sceneManager, DX::DeviceResources* pDeviceResources, DirectX::SimpleMath::Matrix* pProj, DirectX::CommonStates* pStates, DX::StepTimer* pTimer) noexcept(false):
	SceneBace(sceneManager, pDeviceResources, pProj, pStates),
	mp_timer{ pTimer },
	m_buttonEnableTime{ ButtonEnableTime }
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

#if defined(_DEBUG)
	/*デバッグ時の追加初期化処理*/
	// デバッグフォントの作成
	m_debugFont = make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// グリッド床の作成
	m_gridFloor = make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(3.0f, 0.0f, 0.0f));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間[s]</param>
void TitleScene::Update(const float elapsedTime)
{
	// カメラ更新
	m_Camera->Update();

	// ボタンが押せるようになるまでの時間を減らす
	m_buttonEnableTime -= elapsedTime;

	// もし、ボタンが押せるようになるまでの時間が0より大きかった際の早期リターン
	if (m_buttonEnableTime > 0.f) return;

	// ボタンが押せるようになるまでの時間を0にする
	m_buttonEnableTime = 0.f;

	// キーボードの取得
	Keyboard::State kd = Keyboard::Get().GetState();

	// もし、Zキーが押されていて、ボタンが押されるようになっていたらゲームプレイシーンに遷移
	if (kd.Z && m_buttonEnableTime <= 0.f)
		// シーンの遷移
		ChangeScene("Gameplay");
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	/*デバッグ表示*/
#if defined(_DEBUG)
	// グリッドの床の描画
	m_gridFloor->Render(context, view, *mp_Proj);

	// シーン名の表示
	m_debugFont->AddString(0, 0, Colors::White, L"Scene=Title");

	// FPSを取得する
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPSの表示
	m_debugFont->AddString(0, 15, Colors::White, L"FPS=%d", fps);

	// デバッグフォントの描画
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	m_Camera.reset();
}
