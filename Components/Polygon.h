/**
 * @file   Renderer3D.h
 *
 * @brief  ���f���`��R���|�[�l���g�̃w�b�_�[�t�@�C��
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
/// �|���S���̐ݒ�
/// </summary>
class Polygon :
    public RendererBace
{
private:
    // ���S�ƂȂ�g�����X�t�H�[���ւ̃|�C���^
    Transform* mp_Transform;

    // ���_�̑���
    static constexpr int MaxPositionVolume = 3;

    // ���W�f�[�^
    DirectX::SimpleMath::Vector3 m_Positions[MaxPositionVolume];

    // ���_�f�[�^
    DirectX::VertexPosition m_Vertexes[MaxPositionVolume];

    // �C���f�b�N�X
    uint16_t m_Indexes[MaxPositionVolume];

    // �v���~�e�B�u�o�b�`
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_PrimitiveBatch;

public:
    Polygon (SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& position1, const DirectX::SimpleMath::Vector3& position2, const DirectX::SimpleMath::Vector3& position3) noexcept;
    ~Polygon() noexcept;
    void Draw(const DirectX::SimpleMath::Matrix& view) override final;
};

