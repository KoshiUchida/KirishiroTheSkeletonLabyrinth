/**
 * @file   CircleButtonEffect.cpp
 *
 * @brief  円型ボタンのエフェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "CircleButtonEffect.h"

// 関係のあるヘッダー
#include "../Managers/ObjectManager.h"
#include "../Common/Easing.h"

// 使用するコンポーネント
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

/// <summary>
/// Constructor
/// </summary>
CircleButtonEffect::CircleButtonEffect(SceneBace* pScene, const std::string& name, DirectX::SimpleMath::Vector2 position, float size, float limit) noexcept :
	ObjectBace(pScene, name),
	m_Limit{ limit },
	m_Now{ 0.f }
{
	SetLayer(2);

	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);
	pTransform->SetScale(size);

	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "Circle", pTransform, L"Resources\\Textures\\CircleEffect.dds"));
}

/// <summary>
/// Destructor
/// </summary>
CircleButtonEffect::~CircleButtonEffect() noexcept = default;

/// <summary>
///  初期化処理
/// </summary>
void CircleButtonEffect::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void CircleButtonEffect::Process(float elapsedTime)
{
	// 時間の経過を保存
	m_Now += elapsedTime;

	// 時間の経過が上限を越えたら自滅
	if (m_Now > m_Limit)
	{
		mp_ObjectManager->DeleteObject(this);
		return;
	}

	// 時間の経過をパーセントに変換
	float parcent = m_Now / m_Limit;

	// 2次元レンダラーの取得
	Renderer2D* pRenderer = static_cast<Renderer2D*>(GetComponentPtr("Circle"));

	// 透明度の操作
	if (parcent <= 0.3f)
	{
		parcent /= 0.3f;
		pRenderer->SetAlpha(EaseOutQuint(parcent));
	}
	else
	{
		parcent = 0.7f - (parcent - 0.3f);
		pRenderer->SetAlpha(EaseInOutSine(parcent));
	}
}
