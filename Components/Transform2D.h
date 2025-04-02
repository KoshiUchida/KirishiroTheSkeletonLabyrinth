/**
 * @file   Transform2D.h
 *
 * @brief  ２次元トランスフォームのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#pragma once
#include "ComponentsBace.h"

#include "DeviceResources.h"

/// <summary>
/// ２次元トランスフォームコンポネートクラス
/// </summary>
class Transform2D :
	public ComponentsBace
{
public:
	/// <summary>
	/// スクリーン上の中心座標
	/// </summary>
	enum class ScreenOrigin
	{
		Up,
		Down,
		Left,
		Right,
		UpRight,
		UpLeft,
		DownRight,
		DownLeft,
	};

private:
	// 座標
	DirectX::SimpleMath::Vector2 m_Position;
	
	// 回転
	float m_Rotate;
	
	// 大きさ
	DirectX::SimpleMath::Vector2 m_Scale;

	// スクリーン上の中心座標
	ScreenOrigin m_Origin;

public:
	/*Main System*/
	Transform2D(DirectX::SimpleMath::Vector2 position = DirectX::SimpleMath::Vector2::Zero, float rotate = 0.f, DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2(1.f, 1.f), ScreenOrigin origin = ScreenOrigin::UpLeft);
	~Transform2D();

	// Setter
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	void SetRotate(float rotate);
	void SetScale(float scale);
	void SetOrigin(ScreenOrigin origin);

	void SetPositionX(float x);
	void SetPositionY(float y);

	// Getter
	DirectX::SimpleMath::Vector2 GetPosition() const;
	DirectX::SimpleMath::Vector2 GetPosition(DX::DeviceResources* pDevice);
	
	float GetRotate() const;
	DirectX::SimpleMath::Vector2 GetScale () const;

	float GetPositionX() const;
	float GetPositionY() const;
};

