/**
 * @file   GameplayScene.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"
#include "GeometricPrimitive.h"
#include "SkyboxEffect.h"

#if defined(_DEBUG)
// デバッグ必須読み込み
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"
#include "ImaseLib/DebugCamera.h"

#endif

// 前方宣言
class Camera;

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GameplayScene final :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

	// カメラ
    std::unique_ptr<Camera> m_Camera;

    // SkyBox
    std::unique_ptr<DirectX::GeometricPrimitive> m_sky;
    std::unique_ptr<SkyboxEffect> m_effect;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_skyInputLayout;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubemap;


#if defined(_DEBUG)
    /*デバッグ用スマートポインタ*/
    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // グリッドの床
    std::unique_ptr<Imase::GridFloor> m_gridFloor;

    // デバッグカメラ
    std::unique_ptr<Imase::DebugCamera> m_DebugCamera;
#endif

public:
	// Main System
	GameplayScene
    (
        SceneManager* sceneManager,
        DX::DeviceResources* pDeviceResources,
        DirectX::SimpleMath::Matrix* pProj,
        DirectX::CommonStates* pStates,
        DX::StepTimer* pTimer
    ) noexcept(false);
	~GameplayScene () noexcept;
	void Initialize(                       ) final override;
	void Update    (const float elapsedTime) final override;
	void Render    (                       ) final override;
	void Finalize  (                       ) final override;
};

