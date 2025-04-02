/**
 * @file   Player.h
 *
 * @brief  �v���C���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#pragma once
#include "ObjectBace.h"

#include "../Common/Thruster.h"

/// <summary>
/// �v���C���[�I�u�W�F�N�g�N���X
/// </summary>
class Player
	: public ObjectBace
{
private:
	// �X�s�[�h
	Thruster m_MoveSpeed;

	// �U�������Ă��邩
	bool m_IsAttack;

	// �U�����\��
	bool m_CanAttack;

	// �U���̃N�[���^�C��
	float m_AttackCooltime;

	// HP
	int m_HP;
	bool m_Die;

public:
	// Main System
	Player(SceneBace* pScene, const std::string& name) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Process    (float elapsedTime) override final;

	/*HP�֘A*/
	void Damage(int damage);

private:
	/*�����֐�*/
	void Move(float elapsedTime);
	void Attack();

public:
	/*Getter*/
	bool IsAttack() const noexcept;
	bool Die     () const noexcept;
	int  GetHP   () const noexcept;
	int  GetMaxHP() const noexcept;
};

