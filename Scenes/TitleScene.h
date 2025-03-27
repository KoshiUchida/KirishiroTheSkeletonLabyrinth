/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/25
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"

#if defined(_DEBUG)
 // �f�o�b�O�K�{�ǂݍ���
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"

#endif

// �O���錾
class Camera;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // �J����
    std::unique_ptr<Camera> m_Camera;

    // ���݂̃{�^����������悤�ɂȂ�܂ł̎c�莞��
	float m_buttonEnableTime;

    float m_nowTime;

    DirectX::SimpleMath::Matrix m_world;

    std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
    std::unique_ptr<DirectX::Model> m_model;
    
    DirectX::ModelBone::TransformArray m_drawBones;
    DirectX::ModelBone::TransformArray m_animBones;
    
    uint32_t m_leftBackWheelBone;
    uint32_t m_rightBackWheelBone;
    uint32_t m_leftFrontWheelBone;
    uint32_t m_rightFrontWheelBone;
    uint32_t m_leftSteerBone;
    uint32_t m_rightSteerBone;
    uint32_t m_turretBone;
    uint32_t m_cannonBone;
    uint32_t m_hatchBone;

#if defined(_DEBUG)
    /*�f�o�b�O�p�X�}�[�g�|�C���^*/
    // �f�o�b�O�t�H���g
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // �O���b�h�̏�
    std::unique_ptr<Imase::GridFloor> m_gridFloor;

#endif

public:
    // Main System
    TitleScene
    (
        SceneManager* sceneManager,
        DX::DeviceResources* pDeviceResources,
        DirectX::SimpleMath::Matrix* pProj,
        DirectX::CommonStates* pStates,
        DX::StepTimer* pTimer
    ) noexcept(false);
    ~TitleScene() noexcept;

    void Initialize() final override;
    void Update(const float elapsedTime) final override;
    void Render() final override;
    void Finalize() final override;
};
