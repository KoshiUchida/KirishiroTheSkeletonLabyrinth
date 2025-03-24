/**
 * @file   Cylinder.h
 *
 * @brief  円柱オブジェクトのソースファイル
 *
 * @author CatCode
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
    Cylinder(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
    ~Cylinder() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

