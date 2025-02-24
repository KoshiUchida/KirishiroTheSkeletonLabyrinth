/**
 * @file   GameplayScene.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/02/12
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"

#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"
#include "ImaseLib/DebugCamera.h"

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GameplayScene final : public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // グリッドの床
    std::unique_ptr<Imase::GridFloor> m_gridFloor;

    // デバッグカメラ
    std::unique_ptr<Imase::DebugCamera> m_debugCamera;

    // モデル
    std::unique_ptr<DirectX::Model> m_model;

    // プレイヤーの座標
    DirectX::SimpleMath::Vector3 m_position;

    // プレイヤーの向き（Y軸回転：ラジアン）
    float m_rotateY;

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

