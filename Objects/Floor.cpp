/**
 * @file   Floor.cpp
 *
 * @brief  床オブジェクトのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "Floor.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"


/// <summary>
/// Costructor
/// </summary>
Floor::Floor(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);

	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Floor.sdkmesh"));
}

/// <summary>
/// Destructor
/// </summary>
Floor::~Floor() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Floor::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Floor::Process(float elapsedTime)
{
	// 警告回避用
	elapsedTime;
}

