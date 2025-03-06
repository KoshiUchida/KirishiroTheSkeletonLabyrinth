/**
 * @file   ComponentsBace.h
 *
 * @brief  レンダラーコンポート基底クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once
#include "ComponentsBace.h"

/// <summary>
/// レンダラーコンポート基底クラス
/// </summary>
class RendererBace :
    public ComponentsBace
{
protected:
    // 共通ステート
    DirectX::CommonStates* mp_States;

public:
    /*Main System*/
    RendererBace(std::string name, DirectX::CommonStates* pStates);
    virtual ~RendererBace();
    virtual void Draw(const DirectX::SimpleMath::Matrix& view) = 0;
};

