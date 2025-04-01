/**
 * @file   CircleButtonEffect.h
 *
 * @brief  円型ボタンのエフェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// 円型ボタンのエフェクトオブジェクトクラス
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

