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

/// <summary>
/// Constructor
/// </summary>
OparateUI::OparateUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name)
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

	pTransform->SetPosition(DirectX::SimpleMath::Vector2(-140.f, -130.f));

	pTransform->SetOrigin(Transform2D::ScreenOrigin::DownRight);
}

/// <summary>
/// 更新処理
/// </summary>
void OparateUI::Process(float elapsedTime)
{
}
