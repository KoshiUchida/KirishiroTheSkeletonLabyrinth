/**
 * @file   Enemy.h
 *
 * @brief  �G�l�~�[�I�u�W�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/20
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// �G�l�~�[�I�u�W�F�N�g�N���X
/// </summary>
class Enemy :
    public ObjectBace
{
public:
	// Main System
	Enemy(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
	~Enemy() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

