/**
 * @file   Enemy.cpp
 *
 * @brief  エネミーオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/20
 */

#include "pch.h"
#include "Enemy.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 座標の設定
	pTransform->SetPosition(position);

	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, DirectX::SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));
}

/// <summary>
/// Destructor
/// </summary>
Enemy::~Enemy() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Process(float elapsedTime)
{
	elapsedTime;
}
