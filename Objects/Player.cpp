/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "Player.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3DWithAnimation.h"
#include "../Components/BoxCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

// 移動の設定値
static constexpr float MoveSpeedSpeed{ 0.1f };
static constexpr float MoveSpeedA    { 0.06f };
static constexpr float MoveSpeedFC   { 0.95f };

// HPの最大値
static constexpr int MaxHP{ 100 };

// 攻撃のクールタイム
static constexpr float SetAttackCooltime{ 1.7f };

/// <summary>
/// コンストラクト
/// </summary>
Player::Player(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name),
	m_MoveSpeed{ MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC },
	m_IsAttack { false },
	m_CanAttack{ true },
	m_AttackCooltime{ SetAttackCooltime },
	m_HP       { MaxHP },
	m_Die      { false }
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3DWithAnimation>(pScene, "Renderer3D", pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

	pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim");

	static constexpr bool  ShowCollider{ false };
	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f), ShowCollider));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "DamageCollider", pTransform, SimpleMath::Vector3(0.3f, 0.1f, 0.3f)));
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	ColliderBace* pDamageCollider = static_cast<ColliderBace*>(GetComponentPtr("DamageCollider"));

	pDamageCollider->SetOffset(SimpleMath::Vector3(0.7f, 0.f, 0.f));
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Process(float elapsedTime)
{
	m_AttackCooltime -= elapsedTime;
	if (m_AttackCooltime < 0.f)
	{
		m_AttackCooltime = 0.f;
		m_CanAttack = true;
		if (m_IsAttack)
		{
			Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

			pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim");
		}
		m_IsAttack = false;
	}
	else
		m_CanAttack = false;

	// 移動処理
	Move(elapsedTime);

	// 攻撃処理
	Attack();
}

/// <summary>
/// ダメージ処理関数
/// </summary>
void Player::Damage(int damage)
{
	m_HP -= damage;
	
	if (m_HP < 0)
		m_HP = 0;

	m_Die = (m_HP == 0);
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move(float elapsedTime)
{
	// キーボードの入力を取得
	Keyboard::State kb = Keyboard::Get().GetState();

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// コントローラの値
	float cx = { 0.f };
	float cy = { 0.f };

	// 左キーが押されているか
	if (kb.Left || kb.A)
	{
		cx = -1.f;
	}
	// 右キーが押されているか
	if (kb.Right || kb.D)
	{
		cx = 1.f;
	}
	// 上キーが押されているか  
	if (kb.Up || kb.W)
	{
		cy = 1.f;
	}
	// 下キーが押されているか
	if (kb.Down || kb.S)
	{
		cy = -1.f;
	}

	// 移動時の処理
	if (kb.Left || kb.Right || kb.Up || kb.Down ||
		kb.A    || kb.D     || kb.W  || kb.S)
	{
		m_MoveSpeed.Up(elapsedTime);

		pTransform->SetRotateY(std::atan2f(cy, cx));
	}
	// 停止時の処理
	else
	{
		m_MoveSpeed.Stop(elapsedTime);
	}

	// 速度ベクトル
	SimpleMath::Vector3 speed(m_MoveSpeed.Get(), 0.f, 0.f);

	// Y軸で回転する行列を作成
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(pTransform->GetRotateY());
	speed = SimpleMath::Vector3::Transform(speed, rotY);

	// 座標の更新処理
	pTransform->AddPosition(speed);

}

/// <summary>
/// 攻撃処理
/// </summary>
void Player::Attack()
{
	// キーボードの入力を取得
	Keyboard::State kb = Keyboard::Get().GetState();

	// 攻撃キーが押されているか
	if (m_CanAttack && (kb.Z || kb.J))
	{
		if (!m_IsAttack)
		{
			Renderer3DWithAnimation* pRenderer3D = static_cast<Renderer3DWithAnimation*>(GetComponentPtr("Renderer3D"));

			pRenderer3D->SetAnimation(L"Resources\\Models\\KirishiroAttack.sdkmesh_anim");
		}
		m_IsAttack = true;

		m_AttackCooltime = SetAttackCooltime;
	}
}

/// <summary>
/// 攻撃をしているかを取得関数
/// </summary>
bool Player::IsAttack() const noexcept
{
	return m_IsAttack;
}

/// <summary>
/// 死亡したかどうかの取得関数
/// </summary>
bool Player::Die() const noexcept
{
	return m_Die;
}

/// <summary>
/// HPの取得関数
/// </summary>
int Player::GetHP() const noexcept
{
	return m_HP;
}

/// <summary>
/// 最大HPの取得関数
/// </summary>
int Player::GetMaxHP() const noexcept
{
	return MaxHP;
}

