/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/21
 */

#include "pch.h"
#include "Player.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

// 移動の設定値
static constexpr float MoveSpeedSpeed{ 5.f };
static constexpr float MoveSpeedA    { 4.5f };
static constexpr float MoveSpeedFC   { 0.95f };

/// <summary>
/// コンストラクト
/// </summary>
Player::Player(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
	, m_MoveSpeed{ MoveSpeedSpeed, MoveSpeedA, MoveSpeedFC }
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.1f, 0.5f, 0.1f)));
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
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Process(float elapsedTime)
{
	// 移動処理
	Move(elapsedTime);
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move(float elapsedTime)
{
	// キーボードの入力を取得
	Keyboard::State kd = Keyboard::Get().GetState();

	// コントローラの値
	float cx = { 0.f };
	float cy = { 0.f };

	// 左キーが押されているか
	if (kd.Left)
	{
		cx -= 1.f;
	}
	// 右キーが押されているか
	if (kd.Right)
	{
		cx += 1.f;
	}
	// 上キーが押されているか  
	if (kd.Up)
	{
		cy += 1.f;
	}
	// 下キーが押されているか
	if (kd.Down)
	{
		cy -= 1.f;
	}

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 移動時の処理
	if (kd.Left || kd.Right || kd.Up || kd.Down)
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
	pTransform->AddPosition(speed * elapsedTime);

}

