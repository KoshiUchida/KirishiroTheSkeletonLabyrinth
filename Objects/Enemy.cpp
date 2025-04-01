/**
 * @file   Enemy.cpp
 *
 * @brief  エネミーオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "Enemy.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"
#include "../Components/SphereCollider.h"

// 使用するマネージャー
#include "../Managers/ObjectManager.h"

// 関連のあるオブジェクト
#include "Player.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const string& name, const SimpleMath::Vector3& position) noexcept :
	ObjectBace(pScene, name),
	m_Action{ CurrentCourseOfAction::NONE },
	m_SpownPosition{ position }
{
	AddComponent(make_unique<Transform>());

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 座標の設定
	pTransform->SetPosition(m_SpownPosition);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.2f, 0.1f, 0.2f)));
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	static constexpr float OffsetDamageCollider{ 0.7f };
	pDamageCollider->SetOffset(SimpleMath::Vector3(OffsetDamageCollider, 0.f, 0.f));

	static constexpr float PerceptionRange    { 9.f };
	static constexpr bool  ShowPerceptionRange{ false };

	AddComponent(make_unique<SphereCollider>(pScene, "PerceptionRange", pTransform,PerceptionRange, ShowPerceptionRange));
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

	Move();

	Collision();
}

/// <summary>
/// 移動関係処理
/// </summary>
void Enemy::Move()
{
	switch (m_Action)
	{
	case Enemy::CurrentCourseOfAction::NONE:
		break;
	case Enemy::CurrentCourseOfAction::CHASE:
		break;
	default:
		// ERORR : ありえない処理 m_Actionの値を確認してください。
		break;
	}
}

/// <summary>
/// コライダー関係処理
/// </summary>
void Enemy::Collision()
{
	// 自身のコライダーを取得
	ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));

	// プレイヤーの攻撃に対する処理
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	// プレイヤーのコライダーへのポインタ
	ColliderBace* pPlayerCollider;

	if (pPlayer->IsAttack())
	{
		// プレイヤーの攻撃が当たったかどうか
		pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("DamageCollider"));

		if (pCollider->IsHit(pPlayerCollider))
			// エネミーの削除
			mp_ObjectManager->DeleteObject(this);
	}

	// 押し出し処理
	pPlayerCollider = static_cast<ColliderBace*>(pPlayer->GetComponentPtr("Collider"));
	pPlayerCollider->Collision(pCollider);
}
