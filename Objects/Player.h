/**
 * @file   Player.h
 *
 * @brief  �v���C���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/21
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

public:
	// Main System
	Player(SceneBace* pScene, const std::string& name) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Process    (float elapsedTime) override final;

private:
	/*�����֐�*/
	void Move(float elapsedTime);
	void Attack();

public:
	/*Getter Functions*/
	bool IsAttack() const noexcept;
};

