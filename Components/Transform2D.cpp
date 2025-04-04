/**
 * @file   Transform2D.cpp
 *
 * @brief  ２次元トランスフォームのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#include "pch.h"
#include "Transform2D.h"

/// <summary>
/// Constructor
/// </summary>
Transform2D::Transform2D(DirectX::SimpleMath::Vector2 position, float rotate, DirectX::SimpleMath::Vector2 scale, ScreenOrigin origin) :
	ComponentsBace(Tags::NONE, "Transform"),
	m_Position{ position },
	m_Rotate  { rotate },
	m_Scale   { scale },
	m_Origin  { origin }
{
}

/// <summary>
/// Destructor
/// </summary>
Transform2D::~Transform2D() = default;



/*Setter*/

void Transform2D::SetPosition(DirectX::SimpleMath::Vector2 position)
{
	m_Position = position;
}

void Transform2D::SetRotate(float rotate)
{
	m_Rotate = rotate;
}

void Transform2D::SetScale(float scale)
{
	m_Scale = DirectX::SimpleMath::Vector2(scale, scale);
}

void Transform2D::SetOrigin(ScreenOrigin origin)
{
	m_Origin = origin;
}

void Transform2D::SetPositionX(float x)
{
	m_Position.x = x;
}

void Transform2D::SetPositionY(float y)
{
	m_Position.y = y;
}

DirectX::SimpleMath::Vector2 Transform2D::GetPosition() const
{
	return m_Position;
}

DirectX::SimpleMath::Vector2 Transform2D::GetPosition(DX::DeviceResources* pDevice)
{
	// スクリーン上の中心座標
	DirectX::SimpleMath::Vector2 origin;

	// 現在のスクリーンのサイズを取得
	RECT screen = pDevice->GetOutputSize();

	// 現在のオリジンの設定から適する中心座標を取得
	switch (m_Origin)
	{
	case Transform2D::ScreenOrigin::Up:
		origin.x = static_cast<float>(screen.right) / 2.f;
		origin.y = static_cast<float>(screen.top);
		break;
	case Transform2D::ScreenOrigin::Down:
		origin.x = static_cast<float>(screen.right) / 2.f;
		origin.y = static_cast<float>(screen.bottom);
		break;
	case Transform2D::ScreenOrigin::Left:
		origin.x = static_cast<float>(screen.left);
		origin.y = static_cast<float>(screen.bottom) / 2.f;
		break;
	case Transform2D::ScreenOrigin::Right:
		origin.x = static_cast<float>(screen.right);
		origin.y = static_cast<float>(screen.bottom) / 2.f;
		break;
	case Transform2D::ScreenOrigin::UpRight:
		origin.x = static_cast<float>(screen.right);
		origin.y = static_cast<float>(screen.top);
		break;
	case Transform2D::ScreenOrigin::UpLeft:
		origin.x = static_cast<float>(screen.left);
		origin.y = static_cast<float>(screen.top);
		break;
	case Transform2D::ScreenOrigin::DownRight:
		origin.x = static_cast<float>(screen.right);
		origin.y = static_cast<float>(screen.bottom);
		break;
	case Transform2D::ScreenOrigin::DownLeft:
		origin.x = static_cast<float>(screen.left);
		origin.y = static_cast<float>(screen.bottom);
		break;
	default:
		// ERROR : 起こりえない問題 m_Originが正しく設定されていません。
		break;
	}

	// 中心座標からの座標を返す
	return origin + m_Position;
}

float Transform2D::GetRotate() const
{
	return m_Rotate;
}

DirectX::SimpleMath::Vector2 Transform2D::GetScale() const
{
	return m_Scale;
}

float Transform2D::GetPositionX() const
{
	return m_Position.x;
}

float Transform2D::GetPositionY() const
{
	return m_Position.y;
}
