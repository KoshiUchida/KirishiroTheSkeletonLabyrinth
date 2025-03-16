/**
 * @file   MapGenerator.h
 *
 * @brief  �}�b�v�W�F�l���[�^�[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 */

#pragma once
#include "ObjectBace.h"

class MapGenerator :
    public ObjectBace
{
public:
	// Main System
	MapGenerator(SceneBace* pScene) noexcept;
	~MapGenerator() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

