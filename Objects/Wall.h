/**
 * @file   Wall.h
 *
 * @brief  壁オブジェクトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// 壁オブジェクトのクラス
/// </summary>
class Wall :
    public ObjectBace
{
public:
    /*Main System*/
    Wall(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& rotate = DirectX::SimpleMath::Vector3::Zero) noexcept;
    ~Wall() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

