/**
 * @file   Transform.cpp
 *
 * @brief  プレイヤーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#include "pch.h"
#include "Player.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// コンストラクト
/// </summary>
Player::Player(SceneBace* pScene) noexcept(false)
	: ObjectBace(pScene)
	, m_Renderer(pScene, m_Transform.get(), L"Resources\\Models\\Kirishiro.sdkmesh")
{
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
	this->m_Transform->SetScale(0.35f);
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(float elapsedTime)
{
	// キーボードの入力を取得
	auto kd = Keyboard::Get().GetState();

	//float rotateSpeed = 75.f;

	//// 速度ベクトル
	//SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

	//// Y軸で回転する行列を作成する
	//SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);
	//v = SimpleMath::Vector3::Transform(v, rotY);

	// 左キーが押されているか
	if (kd.Left)
	{
		m_Transform->AddPositionX(-1.5f * elapsedTime);
	}

	// 右キーが押されているか
	if (kd.Right)
	{
		m_Transform->AddPositionX(1.5f * elapsedTime);
	}

	// 上キーが押されているか  
	if (kd.Up)
	{
		m_Transform->AddPositionZ(-1.5f * elapsedTime);
	}

	// 下キーが押されているか
	if (kd.Down)
	{
		m_Transform->AddPositionZ(1.5f * elapsedTime);
	}

	//m_position += v * 3.0f * elapsedTime;
}

