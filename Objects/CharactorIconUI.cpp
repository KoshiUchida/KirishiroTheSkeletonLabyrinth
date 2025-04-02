/**
 * @file   CharactorIconUI.cpp
 *
 * @brief  キャラクターアイコンUIのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#include "pch.h"
#include "CharactorIconUI.h"

// 使用するコンポーネント
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

/// <summary>
/// Constructor
/// </summary>
CharactorIconUI::CharactorIconUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name)
{
	SetLayer(2);

	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "UICharacter", pTransform, L"Resources\\Textures\\KirishiroIcon.dds"));
}

/// <summary>
/// Destructor
/// </summary>
CharactorIconUI::~CharactorIconUI() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void CharactorIconUI::Initialize()
{
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(DirectX::SimpleMath::Vector2(250.f, 125.f));

	pTransform->SetScale(0.4f);

	Renderer2D* pUI = static_cast<Renderer2D*>(GetComponentPtr("UICharacter"));

	pUI->SetOffset(DirectX::SimpleMath::Vector2(-190.f, -25.f));
}

/// <summary>
/// 更新処理
/// </summary>
void CharactorIconUI::Process(float elapsedTime)
{
	elapsedTime;
}
