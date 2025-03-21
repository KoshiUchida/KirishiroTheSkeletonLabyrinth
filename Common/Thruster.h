/**
 * @file   Thruster.h
 *
 * @brief  �����N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/20
 */

#pragma once

/// <summary>
/// �����N���X
/// </summary>
class Thruster
{
private:
	// ���݂̉���
	float m_Now;

	// �����̍ő�l
	float m_Max;

	// �����x(acceleration)
	float m_A;

	// ���C�W��(friction coefficient)
	float m_FC;

public:
	/*Main*/
	Thruster(float _speed, float _a, float _fc) noexcept;
	~Thruster() noexcept;

	void Up(float elapsedTime);
	void Stop(float elapsedTime);

	float Get();
};
