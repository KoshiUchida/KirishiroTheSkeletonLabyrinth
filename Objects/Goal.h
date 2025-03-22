/**
 * @file   Goal.h
 *
 * @brief  ゴールオブジェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/22
 */

#pragma once
#include "ObjectBace.h"

class Goal :
    public ObjectBace
{
public:
    /*Main System*/
    Goal(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
    ~Goal() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

