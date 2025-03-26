/**
 * @file   ResultScene.h
 *
 * @brief  リザルトシーンのヘッダファイル
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

    // カメラ
    std::unique_ptr<Camera> m_Camera;

    // 現在のボタンが押せるようになるまでの残り時間
    float m_buttonEnableTime;

#if defined(_DEBUG)
    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // グリッドの床
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

