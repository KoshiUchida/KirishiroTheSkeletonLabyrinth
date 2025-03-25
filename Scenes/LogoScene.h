/**
 * @file   LogoScene.h
 *
 * @brief  ロゴシーンのヘッダファイル
 *
 * @author CatCode
 */

#pragma once
#include "SceneBace.h"

#include <memory>
#include "StepTimer.h"

#if defined(_DEBUG)
 // デバッグ必須読み込み
#include "ImaseLib/DebugFont.h"

#endif

 // 前方宣言
class Camera;

/// <summary>
/// ロゴシーンクラス
/// </summary>
class LogoScene :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // カメラ
    std::unique_ptr<Camera> m_Camera;

    // スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    // 現在の経過時間
    float m_Time;

    // 画面のサイズ
	RECT m_FullscreenRect;



	// ロゴのテクスチャ
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture_Logo;

    // ロゴテクスチャのオリジン
    DirectX::SimpleMath::Vector2 m_LogoOrigin;

    // ロゴテクスチャの座標
    DirectX::SimpleMath::Vector2 m_LogoPos;

    // ロゴの透明度
	float m_LogoAlpha;



	// 背景のテクスチャ
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture_Background;

#if defined(_DEBUG)
    /*デバッグ用スマートポインタ*/
    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

#endif

public:
    /*Main System*/
    LogoScene
    (
        SceneManager* sceneManager,
        DX::DeviceResources* pDeviceResources,
        DirectX::SimpleMath::Matrix* pProj,
        DirectX::CommonStates* pStates,
        DX::StepTimer* pTimer
    ) noexcept(false);
    ~LogoScene() noexcept;

    void Initialize(                       ) final override;
    void Update    (const float elapsedTime) final override;
    void Render    (                       ) final override;
    void Finalize  (                       ) final override;
};

