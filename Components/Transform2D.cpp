/**
 * @file   Transform2D.cpp
 *
 * @brief  ２次元トランスフォームのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#include "pch.h"
#include "Transform2D.h"

/// <summary>
/// Constructor
/// </summary>
Transform2D::Transform2D(DirectX::SimpleMath::Vector2 position, float rotate, float scale) :
	ComponentsBace(Tags::NONE, "Transform"),
	m_Position{ position },
	m_Rotate  { rotate },
	m_Scale   { scale }
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
	m_Scale = scale;
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

float Transform2D::GetRotate() const
{
	return m_Rotate;
}

float Transform2D::GetScale() const
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
