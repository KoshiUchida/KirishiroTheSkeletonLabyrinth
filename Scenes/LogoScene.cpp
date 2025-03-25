/**
 * @file   LogoScene.cpp
 *
 * @brief  ロゴシーンのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "LogoScene.h"

#include "DDSTextureLoader.h"

// 前方宣言
#include "Camera.h"

using namespace std;
using namespace DirectX;

// ロゴのフェードイン時間
static constexpr float LogoFadeInTime{ 3.0f };

// ロゴのアイドル時間
static constexpr float LogoIdolTime{ 1.5f };

// ロゴのフェードアウト時間
static constexpr float LogoFadeOutTime{ 1.5f };

/// <summary>
/// Constructor
/// </summary>
LogoScene::LogoScene(SceneManager* sceneManager, DX::DeviceResources* pDeviceResources, DirectX::SimpleMath::Matrix* pProj, DirectX::CommonStates* pStates, DX::StepTimer* pTimer) noexcept(false):
	SceneBace(sceneManager, pDeviceResources, pProj, pStates),
	mp_timer   { pTimer },
	m_Time     { 0.f },
	m_LogoAlpha{ 0.f },
	m_FullscreenRect{}
{
}

/// <summary>
/// Destructor
/// </summary>
LogoScene::~LogoScene() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void LogoScene::Initialize()
{
	auto device = mp_DeviceResources->GetD3DDevice();
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// 経過時間の初期化
	m_Time = 0.f;

	// カメラの作成
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(3.f, 0.f, 0.f));

	// スプライトバッチの作成
	m_SpriteBatch = make_unique<SpriteBatch>(context);

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;

	m_FullscreenRect = mp_DeviceResources->GetOutputSize();


	
	// ロゴのテクスチャの読み込み
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Resources\\Textures\\Logo.dds",
			resource.GetAddressOf(), m_texture_Logo.ReleaseAndGetAddressOf()));

	// ロゴのテクスチャのサイズを取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> logo;
	DX::ThrowIfFailed(resource.As(&logo));

	CD3D11_TEXTURE2D_DESC logoDesc;
	logo->GetDesc(&logoDesc);

	// ロゴのテクスチャのオリジンの設定
	m_LogoOrigin = SimpleMath::Vector2(logoDesc.Width / 2.f, logoDesc.Height / 2.f);

	// ロゴのテクスチャの座標の設定
	m_LogoPos = SimpleMath::Vector2(m_FullscreenRect.right / 2.f, m_FullscreenRect.bottom / 2.f);

	// ロゴのアルファ値の初期化
	m_LogoAlpha = 0.f;



	// 背景のテクスチャの読み込み
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Resources\\Textures\\LogoBackground.dds", nullptr,
			m_texture_Background.ReleaseAndGetAddressOf()));

#if defined(_DEBUG)
	/*デバッグ時の追加初期化処理*/
	// デバッグフォントの作成
	m_debugFont = std::make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

#endif
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間[s]</param>
void LogoScene::Update(const float elapsedTime)
{
	// 経過時間の加算
	m_Time += elapsedTime;

	// ロゴのアルファ値の更新
	if (m_Time < LogoFadeInTime)
	{
		// ロゴのフェードイン
		m_LogoAlpha = m_Time / LogoFadeInTime;
	}
	else if (m_Time < LogoFadeInTime + LogoIdolTime)
	{
		// ロゴのアイドル
		m_LogoAlpha = 1.f;
	}
	else if (m_Time < LogoFadeInTime + LogoIdolTime + LogoFadeOutTime)
	{
		// ロゴのフェードアウト
		m_LogoAlpha = 1.f - (m_Time - LogoFadeInTime - LogoIdolTime) / LogoFadeOutTime;
	}
	else
	{
		// タイトルシーンに遷移
		ChangeScene("Title");
	}

	// キーボードの取得
	Keyboard::State kd = Keyboard::Get().GetState();

	// もし、Zキーが押されていたらタイトルシーンに遷移
	if (kd.Z)
		// シーンの遷移
		ChangeScene("Title");

	// カメラの更新
	//m_Camera->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void LogoScene::Render()
{
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// 描画処理
	m_SpriteBatch->Begin(SpriteSortMode_Deferred, mp_States->NonPremultiplied());

	// 背景の描画
	m_SpriteBatch->Draw(m_texture_Background.Get(), m_FullscreenRect, Colors::Black);

	// ロゴのサイズ
	static constexpr float logoSize = 0.15f;

	// ロゴの描画
	m_SpriteBatch->Draw(m_texture_Logo.Get(), m_LogoPos, nullptr,
		SimpleMath::Color(1.f, 1.f, 1.f, m_LogoAlpha), 0.f, m_LogoOrigin,
		logoSize
	);

	m_SpriteBatch->End();

#if defined(_DEBUG)
	/*デバッグ表示*/
	// シーンの名前の表示
	m_debugFont->AddString(0, 0, Colors::White, L"Scene:LogoScene");

	// FPSを取得する
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPSの表示
	m_debugFont->AddString(0, 50, Colors::White, L"FPS=%d", fps);

	// デバッグフォントの描画
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void LogoScene::Finalize()
{
	m_Camera     .reset();
	m_debugFont  .reset();
	m_SpriteBatch.reset();

	m_texture_Logo.Reset();
	m_texture_Background.Reset();
}
