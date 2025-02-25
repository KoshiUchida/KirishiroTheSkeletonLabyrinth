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
#include <memory>
#include "DeviceResources.h"
#include "Transform.h"

class SceneBace;

/// <summary>
/// 3Dモデル描画クラス
/// </summary>
class Renderer3D
{
private:
	// トランスフォームへのポインタ
	Transform* mp_Transform;

	// モデル
	std::unique_ptr<DirectX::Model> m_Model;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// 共通ステート
	DirectX::CommonStates* mp_States;

public:
	Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false);
	~Renderer3D() noexcept;
	void Draw(const DirectX::SimpleMath::Matrix& view);
};

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

