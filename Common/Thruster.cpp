/**
 * @file   Thruster.cpp
 *
 * @brief  �����N���X�̃\�[�X�t�@�C��
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
/// <param name="_speed">�ő呬�x</param>
/// <param name="_a">�����x</param>
/// <param name="_fc">���C�x(fc < 1.0)</param>
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
/// ���x�㏸
/// </summary>
/// <param name="elapsedTime">����</param>
void Thruster::Up(float elapsedTime)
{
	m_Now += m_A * elapsedTime;

	if (m_Now > m_Max)
		m_Now = m_Max;
}

/// <summary>
/// ���x�ቺ
/// </summary>
/// <param name="elapsedTime">����</param>
void Thruster::Stop(float elapsedTime)
{
	if (m_Now <= 0.f)
		return;

	m_Now *= m_FC * elapsedTime;
}

/// <summary>
/// �l�̎擾
/// </summary>
float Thruster::Get()
{
	return m_Now;
}
