/**
 * @file   Enemy.h
 *
 * @brief  �G�l�~�[�I�u�W�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

#include "../Common/Thruster.h"

/// <summary>
/// �G�l�~�[�I�u�W�F�N�g�N���X
/// </summary>
class Enemy :
    public ObjectBace
{
public:
	/// <summary>
	/// ���݂̍s���w�j
	/// </summary>
	enum class CurrentCourseOfAction
	{
		NONE,
		CHASE,
	};

private:
	// ���݂̍s���w�j
	CurrentCourseOfAction m_Action;

	// �X�|�[�����W
	DirectX::SimpleMath::Vector3 m_SpownPosition;

	// �v���C���[�����������H
	bool m_PlayerFound;

	// �X�|�[���n�_����߂�����
	bool m_SpawnPointFar;

	// ��]���x
	Thruster m_RotateSpeed;

	// ��]����
	float m_RotatePlusMinus;

	// �v���C���[���U�������ɂ��邩
	bool m_CanAttackPlayer;

	// �X�s�[�h
	Thruster m_MoveSpeed;

public:
	// Main System
	Enemy(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
	~Enemy() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;

private:
	/*��������*/
	void Move(float elapsedTime);
	void Collision();
};

