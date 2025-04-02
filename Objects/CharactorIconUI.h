/**
 * @file   CharactorIconUI.h
 *
 * @brief  キャラクターアイコンUIのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// キャラクターアイコンUIオブジェクトクラス
/// </summary>
class CharactorIconUI :
    public ObjectBace
{
public:
    /*Main System*/
    CharactorIconUI(SceneBace* pScene, const std::string& name) noexcept;
    ~CharactorIconUI() noexcept;

    void Initialize() override final;
    void Process(float elapsedTime) override final;
};

