/**
 * @file   Player.h
 *
 * @brief  プレイヤーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#pragma once
#include "ObjectBace.h"

#include "../Common/Thruster.h"

/// <summary>
/// プレイヤーオブジェクトクラス
/// </summary>
class Player
	: public ObjectBace
{
private:
	// スピード
	Thruster m_MoveSpeed;

	// 攻撃をしているか
	bool m_IsAttack;

	// 攻撃が可能か
	bool m_CanAttack;

	// 攻撃のクールタイム
	float m_AttackCooltime;

	// HP
	int m_HP;
	bool m_Die;

public:
	// Main System
	Player(SceneBace* pScene, const std::string& name) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Process    (float elapsedTime) override final;

	/*HP関連*/
	void Damage(int damage);

private:
	/*内部関数*/
	void Move(float elapsedTime);
	void Attack();

public:
	/*Getter*/
	bool IsAttack() const noexcept;
	bool Die     () const noexcept;
	int  GetHP   () const noexcept;
	int  GetMaxHP() const noexcept;
};

