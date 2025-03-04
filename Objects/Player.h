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
#include "Renderer3D.h"

class SceneBace;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
	: public ObjectBace
{
private:
	// �����_���[
	Renderer3D m_Renderer;

public:
	// Main System
	Player(SceneBace* pScene) noexcept(false);
	~Player() noexcept;

	void Initialize(                 ) override final;
	void Update    (float elapsedTime) override final;

	Renderer3D* GetRenderer3DPointer() { return &m_Renderer; }
};

