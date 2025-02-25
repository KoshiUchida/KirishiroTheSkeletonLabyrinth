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

	// モデル
	std::unique_ptr<DirectX::Model> m_Model;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// 共通ステート
	DirectX::CommonStates* mp_States;

public:
	// Main System
	Player() noexcept;
	~Player() noexcept;

	Player
	(
		        DX::DeviceResources* pDeviceResources,
		DirectX::SimpleMath::Matrix* pProj,
		      DirectX::CommonStates* pStates
	) noexcept(false);

	void Initialize();
	void Update(float elapsedTime);
	void Draw(const DirectX::SimpleMath::Matrix& view);
	void Finalize();

	Transform* GetTransformPointer() { return &m_Transform; }
};

