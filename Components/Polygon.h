/**
 * @file   Renderer3D.h
 *
 * @brief  モデル描画コンポーネントのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */
#pragma once

#include "RendererBace.h"
#include <memory>

class SceneBace;
class Transform;

/// <summary>
/// ポリゴンの設定
/// </summary>
class Polygon :
    public RendererBace
{
private:
    // 中心となるトランスフォームへのポインタ
    Transform* mp_Transform;

    // 頂点の総数
    static constexpr int MaxPositionVolume = 3;

    // 座標データ
    DirectX::SimpleMath::Vector3 m_Positions[MaxPositionVolume];

    // 頂点データ
    DirectX::VertexPosition m_Vertexes[MaxPositionVolume];

    // インデックス
    uint16_t m_Indexes[MaxPositionVolume];

    // プリミティブバッチ
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_PrimitiveBatch;

public:
    Polygon (SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& position1, const DirectX::SimpleMath::Vector3& position2, const DirectX::SimpleMath::Vector3& position3) noexcept;
    ~Polygon() noexcept;
    void Draw(const DirectX::SimpleMath::Matrix& view) override final;
};

