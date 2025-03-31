/**
 * @file   PlayerStatusUI.cpp
 *
 * @brief  プレイヤーステータスUIのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#include "pch.h"
#include "PlayerStatusUI.h"

// 使用するコンポーネント
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

/// <summary>
/// Constructor
/// </summary>
PlayerStatusUI::PlayerStatusUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "UIText", pTransform, L"Resources\\Textures\\PlayerStatusUI.dds"));
}

/// <summary>
/// Destructor
/// </summary>
PlayerStatusUI::~PlayerStatusUI() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void PlayerStatusUI::Initialize()
{
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(DirectX::SimpleMath::Vector2(180.f, 70.f));
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerStatusUI::Process(float elapsedTime)
{
	elapsedTime;
}
