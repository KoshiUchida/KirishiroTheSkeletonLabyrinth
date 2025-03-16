/**
 * @file   MapGenerator.h
 *
 * @brief  マップジェネレーターのヘッダーファイル
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

