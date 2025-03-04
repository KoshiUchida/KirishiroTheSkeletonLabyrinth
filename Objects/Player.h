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
#include "Renderer3D.h"

class SceneBace;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
	: public ObjectBace
{
private:
	// レンダラー
	Renderer3D m_Renderer;

public:
	// Main System
	Player(SceneBace* pScene) noexcept(false);
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Update    (float elapsedTime) override final;

	Renderer3D* GetRenderer3DPointer() { return &m_Renderer; }
};

