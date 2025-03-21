/**
 * @file   Thruster.h
 *
 * @brief  加速クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/20
 */

#pragma once

/// <summary>
/// 加速クラス
/// </summary>
class Thruster
{
private:
	// 現在の加速
	float m_Now;

	// 加速の最大値
	float m_Max;

	// 加速度(acceleration)
	float m_A;

	// 摩擦係数(friction coefficient)
	float m_FC;

public:
	/*Main*/
	Thruster(float _speed, float _a, float _fc) noexcept;
	~Thruster() noexcept;

	void Up(float elapsedTime);
	void Stop(float elapsedTime);

	float Get();
};
