/**
 * @file   Wall.cpp
 *
 * @brief  壁オブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#include "pch.h"
#include "Wall.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"

/// <summary>
/// Constructor
/// </summary>
Wall::Wall(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& rotate) noexcept
	: ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetPosition(position);
	pTransform->SetRotate(rotate);

	AddComponent(std::make_unique<Renderer3D>(mp_Scene, pTransform, L"Resources\\Models\\Wall.sdkmesh"));

}

/// <summary>
/// Destructor
/// </summary>
Wall::~Wall() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Wall::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Wall::Process(float elapsedTime)
{
	// 警告回避用
	elapsedTime;
}
