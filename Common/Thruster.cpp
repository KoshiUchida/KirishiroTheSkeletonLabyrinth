/**
 * @file   Thruster.cpp
 *
 * @brief  加速クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/21
 */

#include "pch.h"
#include "Thruster.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="_speed">最大速度</param>
/// <param name="_a">加速度</param>
/// <param name="_fc">摩擦度(fc < 1.0)</param>
Thruster::Thruster(float _speed, float _a, float _fc) noexcept
	: m_Max{ _speed }
	, m_A  { _a }
	, m_FC { _fc }
	, m_Now{ 0.f }
{
}

/// <summary>
/// Destructor
/// </summary>
Thruster::~Thruster() noexcept = default;

/// <summary>
/// 速度上昇
/// </summary>
/// <param name="elapsedTime">時間</param>
void Thruster::Up(float elapsedTime)
{
	m_Now += m_A * elapsedTime;

	if (m_Now > m_Max)
		m_Now = m_Max;
}

/// <summary>
/// 速度低下
/// </summary>
/// <param name="elapsedTime">時間</param>
void Thruster::Stop(float elapsedTime)
{
	if (m_Now <= 0.f)
		return;

	m_Now *= m_FC * elapsedTime;
}

/// <summary>
/// 値の取得
/// </summary>
float Thruster::Get()
{
	return m_Now;
}
