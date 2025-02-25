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
#include "Transform.h"
#include "Renderer3D.h"

class SceneBace;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
private:
	// トランスフォーム
	Transform m_Transform;

	// レンダラー
	Renderer3D m_Renderer;

public:
	// Main System
	Player(SceneBace* pScene) noexcept(false);
	~Player() noexcept;

	void Initialize();
	void Update(float elapsedTime);

	Transform* GetTransformPointer() { return &m_Transform; }
	Renderer3D* GetRenderer3DPointer() { return &m_Renderer; }
};

