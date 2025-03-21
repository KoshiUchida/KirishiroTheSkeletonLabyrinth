/**
 * @file   Player.h
 *
 * @brief  プレイヤーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/21
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

public:
	// Main System
	Player(SceneBace* pScene) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Process    (float elapsedTime) override final;

private:
	/*内部関数*/
	void Move(float elapsedTime);
};

