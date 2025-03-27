/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/26
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
	m_nowTime{ 0.0f },
	m_leftBackWheelBone(ModelBone::c_Invalid),
	m_rightBackWheelBone(ModelBone::c_Invalid),
	m_leftFrontWheelBone(ModelBone::c_Invalid),
	m_rightFrontWheelBone(ModelBone::c_Invalid),
	m_leftSteerBone(ModelBone::c_Invalid),
	m_rightSteerBone(ModelBone::c_Invalid),
	m_turretBone(ModelBone::c_Invalid),
	m_cannonBone(ModelBone::c_Invalid),
	m_hatchBone(ModelBone::c_Invalid)
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

	m_fxFactory->SetDirectory(L"Resources\\Textures");

	m_model = Model::CreateFromSDKMESH(device, L"Resources\\Models\\Tank.sdkmesh",
		*m_fxFactory,
		ModelLoader_CounterClockwise | ModelLoader_IncludeBones);

	const size_t nbones = m_model->bones.size();

	m_drawBones = ModelBone::MakeArray(nbones);
	m_animBones = ModelBone::MakeArray(nbones);

	m_model->CopyBoneTransformsTo(nbones, m_animBones.get());

	uint32_t index = 0;
	for (const auto& it : m_model->bones)
	{
		if (_wcsicmp(it.name.c_str(), L"tank_geo") == 0)
		{
			m_animBones[index] = XMMatrixIdentity();
		}
		else if (_wcsicmp(it.name.c_str(), L"l_back_wheel_geo") == 0) { m_leftBackWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_back_wheel_geo") == 0) { m_rightBackWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"l_front_wheel_geo") == 0) { m_leftFrontWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_front_wheel_geo") == 0) { m_rightFrontWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"l_steer_geo") == 0) { m_leftSteerBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_steer_geo") == 0) { m_rightSteerBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"turret_geo") == 0) { m_turretBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"canon_geo") == 0) { m_cannonBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"hatch_geo") == 0) { m_hatchBone = index; }


		++index;
	}

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

	m_nowTime += elapsedTime;

	m_world = SimpleMath::Matrix::CreateScale(0.01f);
	m_world *= SimpleMath::Matrix::CreateRotationY(m_nowTime * 0.1f);
	m_world *= SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	
	float wheelRotation = m_nowTime * 5.f;
	float steerRotation = sinf(m_nowTime * 0.75f) * 0.5f;
	float turretRotation = sinf(m_nowTime * 0.333f) * 1.25f;
	float cannonRotation = sinf(m_nowTime * 0.25f) * 0.333f - 0.333f;
	float hatchRotation = std::min(0.f, std::max(sinf(m_nowTime * 2.f) * 2.f, -1.f));

	XMMATRIX mat = XMMatrixRotationX(wheelRotation);
	m_animBones[m_leftFrontWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftFrontWheelBone]);
	m_animBones[m_rightFrontWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightFrontWheelBone]);
	m_animBones[m_leftBackWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftBackWheelBone]);
	m_animBones[m_rightBackWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightBackWheelBone]);

	mat = XMMatrixRotationX(steerRotation);
	m_animBones[m_leftSteerBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftSteerBone]);
	m_animBones[m_rightSteerBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightSteerBone]);

	mat = XMMatrixRotationY(turretRotation);
	m_animBones[m_turretBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_turretBone]);

	mat = XMMatrixRotationX(cannonRotation);
	m_animBones[m_cannonBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_cannonBone]);

	mat = XMMatrixRotationX(hatchRotation);
	m_animBones[m_hatchBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_hatchBone]);

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
	// デバッグカメラからビュー行列を取得する
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// コンテキストの取得
	auto context = mp_DeviceResources->GetD3DDeviceContext();
	size_t nbones = m_model->bones.size();

	m_model->CopyAbsoluteBoneTransforms(nbones,
		m_animBones.get(), m_drawBones.get());

	m_model->Draw(context, *mp_States, nbones, m_drawBones.get(),
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
