/**
 * @file   Renderer3D.h
 *
 * @brief  モデル描画コンポーネントのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */

#include "pch.h"
#include "Polygon.h"

#include "../Scenes/SceneBace.h"
#include "Transform.h"

Polygon::Polygon(SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& position1, const DirectX::SimpleMath::Vector3& position2, const DirectX::SimpleMath::Vector3& position3) noexcept
	: RendererBace(name, pScene->GetCommonStatesPointer())
    , m_Vertexes  {}
	, m_Indexes   { 0, 1, 2 }
    , m_Positions { position1, position2, position3 }
    , mp_Transform{ pTransform }
{
    // プリミティブバッチの作成
    m_PrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>>(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext());

    // Vertexの設定
    for (int i{ 0 }; i < MaxPositionVolume; i++)
        // ToDo::スケールを乗算しているが後で修正
        m_Vertexes[i].position = m_Positions[i];
}

Polygon::~Polygon() noexcept = default;

void Polygon::Draw(const DirectX::SimpleMath::Matrix& view)
{
    // プリミティブバッチの描画
    m_PrimitiveBatch->Begin();

    // 描画
    m_PrimitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, m_Indexes, MaxPositionVolume, m_Vertexes, MaxPositionVolume);

    // 描画の終了
    m_PrimitiveBatch->End();
}
