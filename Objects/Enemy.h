/**
 * @file   Enemy.h
 *
 * @brief  エネミーオブジェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

#include "../Common/Thruster.h"

/// <summary>
/// エネミーオブジェクトクラス
/// </summary>
class Enemy :
    public ObjectBace
{
public:
	/// <summary>
	/// 現在の行動指針
	/// </summary>
	enum class CurrentCourseOfAction
	{
		NONE,
		CHASE,
	};

private:
	// 現在の行動指針
	CurrentCourseOfAction m_Action;

	// スポーン座標
	DirectX::SimpleMath::Vector3 m_SpownPosition;

	// プレイヤーを見つけたか？
	bool m_PlayerFound;

	// スポーン地点から過ぎたか
	bool m_SpawnPointFar;

	// 回転速度
	Thruster m_RotateSpeed;

	// 回転方向
	float m_RotatePlusMinus;

	// プレイヤーが攻撃圏内にいるか
	bool m_CanAttackPlayer;

	// スピード
	Thruster m_MoveSpeed;

public:
	// Main System
	Enemy(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
	~Enemy() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;

private:
	/*内部処理*/
	void Move(float elapsedTime);
	void Collision();
};

