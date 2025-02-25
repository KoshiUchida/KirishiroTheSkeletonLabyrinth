/**
 * @file   Player.h
 *
 * @brief  プレイヤーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#pragma once
#include <memory>
#include "DeviceResources.h"

/// <summary>
/// トランスフォームクラス
/// </summary>
class Transform
{
private:
	// 座標
	DirectX::SimpleMath::Vector3 m_Position;

	// 向き（ラジアン値）
	DirectX::SimpleMath::Vector3 m_Rotate;

	// 大きさ
	DirectX::SimpleMath::Vector3 m_Scale;

public:
	Transform() noexcept;
	~Transform() noexcept;

	// Setter
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate);
	void SetScale(const DirectX::SimpleMath::Vector3& scale);

	void SetScale(float scale);

	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);

	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	// Getter
	DirectX::SimpleMath::Vector3 GetPosition() const;
	DirectX::SimpleMath::Vector3 GetRotate()   const;
	DirectX::SimpleMath::Vector3 GetScale()    const;

	float GetPositionX() const;
	float GetPositionY() const;
	float GetPositionZ() const;

	float GetRotateX() const;
	float GetRotateY() const;
	float GetRotateZ() const;

	float GetScaleX() const;
	float GetScaleY() const;
	float GetScaleZ() const;

	// Addition
	void AddPositionX(float x);
	void AddPositionY(float y);
	void AddPositionZ(float z);
	void AddRotateX(float x);
	void AddRotateY(float y);
	void AddRotateZ(float z);
	void AddScaleX(float x);
	void AddScaleY(float y);
	void AddScaleZ(float z);
};

/// <summary>
/// 3Dモデル描画クラス
/// </summary>
class Renderer3D
{
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

