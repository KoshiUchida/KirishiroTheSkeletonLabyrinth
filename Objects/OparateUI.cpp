/**
 * @file   OparateUI.cpp
 *
 * @brief  オペレータUIオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "OparateUI.h"

 // 使用するコンポーネント
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

// 関係する管理クラス
#include "../Managers/ObjectManager.h"

// 関係するオブジェクト
#include "CircleButtonEffect.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
OparateUI::OparateUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name),
	m_EffectCount{ 0 },
	m_Key{}
{
	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "MainUI", pTransform, L"Resources\\Textures\\OparationUI.dds"));
}

/// <summary>
/// Destructor
/// </summary>
OparateUI::~OparateUI() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void OparateUI::Initialize()
{
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(SimpleMath::Vector2(-140.f, -130.f));

	pTransform->SetOrigin(Transform2D::ScreenOrigin::DownRight);
}

/// <summary>
/// 更新処理
/// </summary>
void OparateUI::Process(float elapsedTime)
{
	// 警告回避
	elapsedTime;

	// エフェクトとの座標の違い
	static constexpr float EffectOffset{ 70.f };

	// エフェクトの表示時間[s]
	static constexpr float EffectLimit{ 0.9f };

	// エフェクトの大きさ
	static constexpr float EffectScale{ 0.4f };

	// キーボードの状態取得
	Keyboard::State kb = Keyboard::Get().GetState();

	// トランスフォームの取得
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	// レンダラーの取得
	Renderer2D* pRnderer = static_cast<Renderer2D*>(GetComponentPtr("MainUI"));

	// エフェクトカウントが100を越えていたらリセット
	if (m_EffectCount > 100)
		m_EffectCount = 0;

	// もし、キー状態がTUREになっていたら現在の状態を入力
	if (m_Key.up)
		m_Key.up    = kb.C || kb.I;
	if (m_Key.down)
		m_Key.down  = kb.X || kb.K;
	if (m_Key.left)
		m_Key.left  = kb.Z || kb.J;
	if (m_Key.right)
		m_Key.right = kb.V || kb.L;

	// キーに応じたエフェクトの生成
	// 上キーが押されているか  
	if (m_Key.up == false && (kb.C || kb.I))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene,
				GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(0.f, -EffectOffset),
				EffectScale,
				EffectLimit
				)
		);

		m_Key.up = true;
	}
	// 下キーが押されているか
	if (m_Key.down == false && (kb.X || kb.K))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(0.f, EffectOffset),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.down = true;
	}
	// 左キーが押されているか
	if (m_Key.left == false && (kb.Z || kb.J))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(-EffectOffset, 0.f),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.left = true;
	}
	// 右キーが押されているか
	if (m_Key.right == false && (kb.V || kb.L))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(EffectOffset, 0.f),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.right = true;
	}
}
