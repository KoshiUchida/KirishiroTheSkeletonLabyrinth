/**
 * @file   Player.h
 *
 * @brief  プレイヤーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#pragma once
#include "ObjectBace.h"

class SceneBace;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
	: public ObjectBace
{
public:
	// Main System
	Player(SceneBace* pScene) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Update    (float elapsedTime) override final;
};

