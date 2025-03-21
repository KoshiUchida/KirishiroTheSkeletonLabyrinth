/**
 * @file   Floor.h
 *
 * @brief  床オブジェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/21
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// 床オブジェクトクラス
/// </summary>
class Floor :
    public ObjectBace
{
public:
    /*Main System*/
    Floor(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero) noexcept;
    ~Floor() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

