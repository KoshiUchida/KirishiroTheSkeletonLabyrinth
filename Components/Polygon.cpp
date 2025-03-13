/**
 * @file   Renderer3D.h
 *
 * @brief  ���f���`��R���|�[�l���g�̃\�[�X�t�@�C��
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
    // �v���~�e�B�u�o�b�`�̍쐬
    m_PrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>>(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext());

    // Vertex�̐ݒ�
    for (int i{ 0 }; i < MaxPositionVolume; i++)
        // ToDo::�X�P�[������Z���Ă��邪��ŏC��
        m_Vertexes[i].position = m_Positions[i];
}

Polygon::~Polygon() noexcept = default;

void Polygon::Draw(const DirectX::SimpleMath::Matrix& view)
{
    // �v���~�e�B�u�o�b�`�̕`��
    m_PrimitiveBatch->Begin();

    // �`��
    m_PrimitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, m_Indexes, MaxPositionVolume, m_Vertexes, MaxPositionVolume);

    // �`��̏I��
    m_PrimitiveBatch->End();
}
