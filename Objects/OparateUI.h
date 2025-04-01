/**
 * @file   OparateUI.h
 *
 * @brief  操作UIオブジェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// 操作UIオブジェクトクラス
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

