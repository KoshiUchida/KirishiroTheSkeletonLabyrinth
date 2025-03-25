/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
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
