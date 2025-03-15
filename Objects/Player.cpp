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

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

#include "../Managers/ObjectManager.h"

using namespace DirectX;

/// <summary>
/// コンストラクト
/// </summary>
Player::Player(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(0.5f, 1.f, 1.f)));
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
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetScale(0.35f);
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Process(float elapsedTime)
{
	// キーボードの入力を取得
	auto kd = Keyboard::Get().GetState();

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	//float rotateSpeed = 75.f;

	//// 速度ベクトル
	//SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

	//// Y軸で回転する行列を作成する
	//SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);
	//v = SimpleMath::Vector3::Transform(v, rotY);

	// 左キーが押されているか
	if (kd.Left)
	{
		pTransform->AddPositionX(-2.5f * elapsedTime);
	}

	// 右キーが押されているか
	if (kd.Right)
	{
		pTransform->AddPositionX(2.5f * elapsedTime);
	}

	// 上キーが押されているか  
	if (kd.Up)
	{
		pTransform->AddPositionZ(-2.5f * elapsedTime);
	}

	// 下キーが押されているか
	if (kd.Down)
	{
		pTransform->AddPositionZ(2.5f * elapsedTime);
	}

	//m_position += v * 3.0f * elapsedTime;

	// 重なり処理
	if (
		static_cast<ColliderBace*>(GetComponentPtr("Collider"))
		->Collider(
			static_cast<ColliderBace*>(GetObjectPtr("Sample")->GetComponentPtr("Collider"))
		))
	{
		pTransform->SetPosition(SimpleMath::Vector3());
	}
}

