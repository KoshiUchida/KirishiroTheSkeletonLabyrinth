/**
 * @file   Transform.cpp
 *
 * @brief  トランスフォームのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#include "pch.h"
#include "Transform.h"

Transform::Transform() noexcept
	: ComponentsBace(Tags::NONE , "Transform")
	, m_Position{}
	, m_Rotate{}
	, m_Scale(1.0f, 1.0f, 1.0f)
{
}

Transform::~Transform() noexcept = default;

/*Setter Functions*/

void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Position = position;
}

void Transform::SetRotate(const DirectX::SimpleMath::Vector3& rotate)
{
	m_Rotate = rotate;
}

void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_Scale = scale;
}

void Transform::SetScale(float scale)
{
	m_Scale = DirectX::SimpleMath::Vector3(scale, scale, scale);
}

void Transform::SetPositionX(float x)
{
	m_Position.x = x;
}

void Transform::SetPositionY(float y)
{
	m_Position.y = y;
}

void Transform::SetPositionZ(float z)
{
	m_Position.z = z;
}

void Transform::SetRotateX(float x)
{
	m_Rotate.x = x;
}

void Transform::SetRotateY(float y)
{
	m_Rotate.y = y;
}

void Transform::SetRotateZ(float z)
{
	m_Rotate.z = z;
}

void Transform::SetScaleX(float x)
{
	m_Scale.x = x;
}

void Transform::SetScaleY(float y)
{
	m_Scale.y = y;
}

void Transform::SetScaleZ(float z)
{
	m_Scale.z = z;
}


/*Getter Functions*/

DirectX::SimpleMath::Vector3 Transform::GetPosition() const
{
	return m_Position;
}

DirectX::SimpleMath::Vector3 Transform::GetRotate() const
{
	return m_Rotate;
}

DirectX::SimpleMath::Vector3 Transform::GetScale() const
{
	return m_Scale;
}

float Transform::GetPositionX() const
{
	return m_Position.x;
}

float Transform::GetPositionY() const
{
	return m_Position.y;
}

float Transform::GetPositionZ() const
{
	return m_Position.z;
}

float Transform::GetRotateX() const
{
	return m_Rotate.x;
}

float Transform::GetRotateY() const
{
	return m_Rotate.y;
}

float Transform::GetRotateZ() const
{
	return m_Rotate.z;
}

float Transform::GetScaleX() const
{
	return m_Scale.x;
}

float Transform::GetScaleY() const
{
	return m_Scale.y;
}

float Transform::GetScaleZ() const
{
	return m_Scale.z;
}


/*Addition*/

void Transform::AddPositionX(float x)
{
	m_Position.x += x;
}

void Transform::AddPositionY(float y)
{
	m_Position.y += y;
}

void Transform::AddPositionZ(float z)
{
	m_Position.z += z;
}

void Transform::AddRotateX(float x)
{
	m_Rotate.x += x;
}

void Transform::AddRotateY(float y)
{
	m_Rotate.y += y;
}

void Transform::AddRotateZ(float z)
{
	m_Rotate.z += z;
}

void Transform::AddScaleX(float x)
{
	m_Scale.x += x;
}

void Transform::AddScaleY(float y)
{
	m_Scale.y += y;
}

void Transform::AddScaleZ(float z)
{
	m_Scale.z += z;
}