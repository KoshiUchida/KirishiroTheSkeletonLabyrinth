/**
 * @file   TitleScene.h
 *
 * @brief  タイトルシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"

#include "Animation.h"

#if defined(_DEBUG)
 // デバッグ必須読み込み
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"

#endif

// 前方宣言
class Camera;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // カメラ
    std::unique_ptr<Camera> m_Camera;

    // 現在のボタンが押せるようになるまでの残り時間
	float m_buttonEnableTime;

    float m_nowTime;

    DirectX::SimpleMath::Matrix m_world;

    std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
    std::unique_ptr<DirectX::Model> m_model;
    
    DirectX::ModelBone::TransformArray m_drawBones;
    
    DX::AnimationSDKMESH m_animation;

#if defined(_DEBUG)
    /*デバッグ用スマートポインタ*/
    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // グリッドの床
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
