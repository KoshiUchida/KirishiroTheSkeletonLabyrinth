/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
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
	m_buttonEnableTime{ ButtonEnableTime },
	m_nowTime{ 0.0f }
{
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
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(9.0f, 7.0f, 9.0f));

	auto device = mp_DeviceResources->GetD3DDevice();

	m_nowTime = 0.0f;

	m_fxFactory = make_unique<EffectFactory>(device);

	m_model = Model::CreateFromSDKMESH(device, L"Resources\\Models\\Kirishiro.sdkmesh",
		*m_fxFactory,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);

	DX::ThrowIfFailed(
		m_animation.Load(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim")
	);

	m_animation.Bind(*m_model);

	m_drawBones = ModelBone::MakeArray(m_model->bones.size());

	m_model->UpdateEffects([&](IEffect* effect)
		{
			auto skin = dynamic_cast<SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		}
	);


#if defined(_DEBUG)
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	/*デバッグ時の追加初期化処理*/
	// デバッグフォントの作成
	m_debugFont = make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// グリッド床の作成
	m_gridFloor = make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間[s]</param>
void TitleScene::Update(const float elapsedTime)
{
	// カメラ更新
	m_Camera->Update();

	m_animation.Update(elapsedTime);

	m_nowTime += elapsedTime;

	m_world = SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	// ボタンが押せるようになるまでの時間を減らす
	m_buttonEnableTime -= elapsedTime;

	// もし、ボタンが押せるようになるまでの時間が0より大きかった際の早期リターン
	if (m_buttonEnableTime > 0.f) return;

	// ボタンが押せるようになるまでの時間を0にする
	m_buttonEnableTime = 0.f;

	// キーボードの取得
	Keyboard::State kb = Keyboard::Get().GetState();

	// もし、何かしらのアクションキーが押されていて、ボタンが押されるようになっていたらゲームプレイシーンに遷移
	if ((kb.C || kb.I || kb.X || kb.K || kb.Z || kb.J || kb.V || kb.L) && m_buttonEnableTime <= 0.f)
		// シーンの遷移
		ChangeScene("Gameplay");
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// コンテキストの取得
	auto context = mp_DeviceResources->GetD3DDeviceContext();
	size_t nbones = m_model->bones.size();

	m_animation.Apply(*m_model, nbones, m_drawBones.get());

	m_model->DrawSkinned(context, *mp_States, nbones, m_drawBones.get(),
		m_world, view, *mp_Proj);

#if defined(_DEBUG)
	/*デバッグ表示*/

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

	m_fxFactory.reset();
	m_model.reset();

#if defined(_DEBUG)
	/*デバッグ時の追加終了処理*/
	m_debugFont.reset();
	m_gridFloor.reset();
#endif
}
