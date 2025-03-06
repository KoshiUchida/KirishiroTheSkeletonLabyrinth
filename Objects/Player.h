/**
 * @file   Player.h
 *
 * @brief  �v���C���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#pragma once
#include "ObjectBace.h"

class SceneBace;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
	: public ObjectBace
{
public:
	// Main System
	Player(SceneBace* pScene) noexcept;
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Update    (float elapsedTime) override final;
};

