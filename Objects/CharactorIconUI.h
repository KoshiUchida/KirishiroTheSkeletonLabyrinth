/**
 * @file   CharactorIconUI.h
 *
 * @brief  �L�����N�^�[�A�C�R��UI�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// �L�����N�^�[�A�C�R��UI�I�u�W�F�N�g�N���X
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

