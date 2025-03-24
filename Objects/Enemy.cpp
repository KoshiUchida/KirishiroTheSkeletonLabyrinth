/**
 * @file   Enemy.cpp
 *
 * @brief  エネミーオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/23
 */

#include "pch.h"
#include "Enemy.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

// 使用するマネージャー
#include "../Managers/ObjectManager.h"

// 関連のあるオブジェクト
#include "Player.h"

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
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
	// 警告回避用
	elapsedTime;

	// プレイヤーの攻撃に対する処理
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	if (pPlayer->IsAttack())
	{
		// プレイヤーの攻撃が当たったかどうか
		ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));
		ColliderBace* pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("DamageCollider"));

		if (pCollider->IsHit(pPlayerCollider))
		{
			// エネミーの削除
			mp_ObjectManager->DeleteObject(this);
		}
	}
}
