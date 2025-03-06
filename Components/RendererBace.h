/**
 * @file   ComponentsBace.h
 *
 * @brief  �����_���[�R���|�[�g���N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once
#include "ComponentsBace.h"

/// <summary>
/// �����_���[�R���|�[�g���N���X
/// </summary>
class RendererBace :
    public ComponentsBace
{
protected:
    // ���ʃX�e�[�g
    DirectX::CommonStates* mp_States;

public:
    /*Main System*/
    RendererBace(std::string name, DirectX::CommonStates* pStates);
    virtual ~RendererBace();
    virtual void Draw(const DirectX::SimpleMath::Matrix& view) = 0;
};

