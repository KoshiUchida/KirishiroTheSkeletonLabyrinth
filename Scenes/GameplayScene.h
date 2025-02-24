/**
 * @file   GameplayScene.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"

#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"
#include "ImaseLib/DebugCamera.h"

class Player;

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

    // プレイヤー
    std::unique_ptr<Player> m_player;

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

