/**
 * @file   Transform.h
 *
 * @brief  トランスフォームのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#pragma once
#include "ComponentsBace.h"

/// <summary>
/// トランスフォームクラス
/// </summary>
class Transform
	: public ComponentsBace
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

