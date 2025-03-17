/**
 * @file   Cylinder.h
 *
 * @brief  円柱オブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/18
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// 円柱オブジェクトクラス
/// </summary>
class Cylinder :
    public ObjectBace
{
public:
    /*Main System*/
    Cylinder(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
    ~Cylinder() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

