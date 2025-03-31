/**
 * @file   PlayerStatusUI.h
 *
 * @brief  �v���C���[�X�e�[�^�XUI�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// �v���C���[�X�e�[�^�XUI�I�u�W�F�N�g�N���X
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

