/**
 * @file   PlayerStatusUI.h
 *
 * @brief  プレイヤーステータスUIのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// プレイヤーステータスUIオブジェクトクラス
/// </summary>
class PlayerStatusUI :
    public ObjectBace
{
public:
    /*Main System*/
    PlayerStatusUI(SceneBace* pScene, const std::string& name) noexcept;
    ~PlayerStatusUI() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

