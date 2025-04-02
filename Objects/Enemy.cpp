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

// 回転の設定値
static constexpr float RotateSpeedSpeed{ XM_PI / 24.f };
static constexpr float RotateSpeedA{ XM_PI / 26.f };
static constexpr float RotateSpeedFC{ 0.95f };

// 回転停止の範囲
static constexpr float RotateRange{ XM_PI / 24.f };

// 移動の設定値
static constexpr float MoveSpeedSpeed{ 0.05f };
static constexpr float MoveSpeedA{ 0.03f };
static constexpr float MoveSpeedFC{ 0.95f };

/// <summary>
/// Constructor
/// </summary>
Enemy::Enemy(SceneBace* pScene, const string& name, const SimpleMath::Vector3& position) noexcept :
	ObjectBace(pScene, name),
	m_Action{ CurrentCourseOfAction::NONE },
	m_SpownPosition  { position },
	m_PlayerFound    { false },
	m_SpawnPointFar  { false },
	m_RotateSpeed    { RotateSpeedSpeed, RotateSpeedA, RotateSpeedFC },
	m_RotatePlusMinus{ 0.f },
	m_CanAttackPlayer{ false },
	m_MoveSpeed      { MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC }
{
	AddComponent(make_unique<Transform>());

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 座標の設定
	pTransform->SetPosition(m_SpownPosition);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Skeleton.sdkmesh"));

	static constexpr bool  ShowCollider{ false };
	AddComponent(make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f), ShowCollider));

	AddComponent(make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.2f, 0.1f, 0.2f)));
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	static constexpr float OffsetDamageCollider{ 0.7f };
	pDamageCollider->SetOffset(SimpleMath::Vector3(OffsetDamageCollider, 0.f, 0.f));

	static constexpr float PerceptionRange    { 5.f };
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
	Move(elapsedTime);

	Collision();
}

/// <summary>
/// 移動関係処理
/// </summary>
void Enemy::Move(float elapsedTime)
{
	// 自身の座標を取得
	Transform* thisTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ターゲットのいる方向
	float targetDirection = thisTransform->GetRotateY();

	// 動きを止めるか
	bool stop{ false };

	switch (m_Action)
	{
	case Enemy::CurrentCourseOfAction::NONE:
		{
			// スポーン地点方向を取得
			if (m_SpawnPointFar)
				targetDirection = XM_PI / -2.f + atan2f((m_SpownPosition.x - thisTransform->GetPositionX()), (m_SpownPosition.z - thisTransform->GetPositionZ()));

			stop = !m_SpawnPointFar;

			// プレイヤーを知覚した場合CHASEに
			if (m_PlayerFound)
				m_Action = CurrentCourseOfAction::CHASE;
			break;
		}
	case Enemy::CurrentCourseOfAction::CHASE:
		{
			// プレイヤーのトランスフォームを取得
			Transform* pPlayerTransform = static_cast<Transform*>(GetObjectPtr("Player")->GetComponentPtr("Transform"));

			// プレイヤーのいる方向を取得
			targetDirection = XM_PI / -2.f + atan2f((pPlayerTransform->GetPositionX() - thisTransform->GetPositionX()), (pPlayerTransform->GetPositionZ() - thisTransform->GetPositionZ()));

			// もし、攻撃ができる場合に立ち止まる
			stop = m_CanAttackPlayer;

			// プレイヤーが知覚外にいる場合NONEに
			if (!m_PlayerFound)
				m_Action = CurrentCourseOfAction::NONE;

			break;
		}
	default:
		// ERORR : ありえない処理 m_Actionの値を確認してください。
		break;
	}

	// 現在の方向からの差分別処理
	if (thisTransform->GetRotateY() >= targetDirection - RotateRange / 2.f && thisTransform->GetRotateY() <= targetDirection + RotateRange / 2.f)
		m_RotateSpeed.Stop(elapsedTime);

	else
	{
		m_RotateSpeed.Up(elapsedTime);

		if (thisTransform->GetRotateY() < targetDirection - RotateRange / 2.f)
			m_RotatePlusMinus = 1.f;
		else if (thisTransform->GetRotateY() > targetDirection + RotateRange / 2.f)
			m_RotatePlusMinus = -1.f;
	}

	// 自身の回転
	if (m_RotateSpeed.Get() != 0.f && m_RotatePlusMinus != 0.f)
		thisTransform->AddRotateY(m_RotateSpeed.Get() * m_RotatePlusMinus);

	//もし、攻撃ができる状態ではなかった場合
	if (!stop)
	{
		m_MoveSpeed.Up(elapsedTime);
	}
	else
	{
		m_MoveSpeed.Stop(elapsedTime);
	}

	if (m_MoveSpeed.Get() != 0.f)
	{

		// 速度ベクトル
		SimpleMath::Vector3 speed(m_MoveSpeed.Get(), 0.f, 0.f);

		// Y軸で回転する行列を作成
		SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(thisTransform->GetRotateY());
		speed = SimpleMath::Vector3::Transform(speed, rotY);

		// 座標の更新処理
		thisTransform->AddPosition(speed);
	}
}

/// <summary>
/// コライダー関係処理
/// </summary>
void Enemy::Collision()
{
	// 自身のコライダーを取得
	ColliderBace* pCollider = static_cast<ColliderBace*>(GetComponentPtr("Collider"));

	// プレイヤーの取得
	Player* pPlayer = static_cast<Player*>(mp_ObjectManager->GetObjectPtr("Player"));

	// プレイヤーのコライダーへのポインタ
	ColliderBace* pPlayerCollider;

	// プレイヤーの攻撃に対する処理
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

	// 知覚範囲の取得
	SphereCollider* pPerceptionRange = static_cast<SphereCollider*>(GetComponentPtr("PerceptionRange"));

	// プレイヤーが知覚範囲にいるか
	m_PlayerFound = pPerceptionRange->IsHit(pPlayerCollider->GetPosition());

	// スポーン地点から離れすぎていないか
	m_SpawnPointFar = !(pPerceptionRange->IsHit(m_SpownPosition));

	// 自身の攻撃がプレイヤーに届くか
	pCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	m_CanAttackPlayer = pCollider->IsHit(pPlayerCollider);
}
