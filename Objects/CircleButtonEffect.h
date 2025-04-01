/**
 * @file   CircleButtonEffect.h
 *
 * @brief  �~�^�{�^���̃G�t�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// �~�^�{�^���̃G�t�F�N�g�I�u�W�F�N�g�N���X
/// </summary>
class CircleButtonEffect :
    public ObjectBace
{
private:
	float m_Limit;
	float m_Now;

public:
	// Main System
	CircleButtonEffect(SceneBace* pScene, const std::string& name, DirectX::SimpleMath::Vector2 position, float size, float limit) noexcept;
	~CircleButtonEffect() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

