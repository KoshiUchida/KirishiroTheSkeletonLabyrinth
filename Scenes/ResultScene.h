/**
 * @file   ResultScene.h
 *
 * @brief  ���U���g�V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/26
 */

#pragma once
#include "SceneBace.h"

#include "StepTimer.h"
#include "Camera.h"

#if defined(_DEBUG)
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"

#endif

class ResultScene final:
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // �J����
    std::unique_ptr<Camera> m_Camera;

    // ���݂̃{�^����������悤�ɂȂ�܂ł̎c�莞��
    float m_buttonEnableTime;

#if defined(_DEBUG)
    // �f�o�b�O�t�H���g
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // �O���b�h�̏�
    std::unique_ptr<Imase::GridFloor> m_gridFloor;
#endif

public:
    /*Main System*/
    ResultScene(
                       SceneManager* sceneManager,
                DX::DeviceResources* pDeviceResources,
        DirectX::SimpleMath::Matrix* pProj,
              DirectX::CommonStates* pStates,
                      DX::StepTimer* pTimer
    ) noexcept(false);

    ~ResultScene() noexcept;

    void Initialize(                       ) final override;
    void Update    (const float elapsedTime) final override;
    void Render    (                       ) final override;
    void Finalize  (                       ) final override;
};

