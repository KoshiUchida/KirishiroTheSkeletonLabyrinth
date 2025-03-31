/**
 * @file   Transform2D.h
 *
 * @brief  ２次元トランスフォームのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "ComponentsBace.h"

/// <summary>
/// ２次元トランスフォームコンポネートクラス
/// </summary>
class Transform2D :
	public ComponentsBace
{
private:
	DirectX::SimpleMath::Vector2 m_Position;
	float m_Rotate;
	float m_Scale;

public:
	/*Main System*/
	Transform2D(DirectX::SimpleMath::Vector2 position = DirectX::SimpleMath::Vector2::Zero, float rotate = 0.f, float scale = 1.f);
	~Transform2D();

	// Setter
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	void SetRotate(float rotate);
	void SetScale(float scale);

	void SetPositionX(float x);
	void SetPositionY(float y);

	// Getter
	DirectX::SimpleMath::Vector2 GetPosition() const;
	
	float GetRotate() const;
	float GetScale () const;

	float GetPositionX() const;
	float GetPositionY() const;
};

