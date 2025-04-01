/**
 * @file   OparateUI.h
 *
 * @brief  ����UI�I�u�W�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// ����UI�I�u�W�F�N�g�N���X
/// </summary>
class OparateUI :
    public ObjectBace
{
private:
	int m_EffectCount;

	struct KeyStatusFlag
	{
		bool up;
		bool down;
		bool left;
		bool right;
	} m_Key;

public:
	// Main System
	OparateUI(SceneBace* pScene, const std::string& name) noexcept;
	~OparateUI() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

