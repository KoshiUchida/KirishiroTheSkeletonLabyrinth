/**
 * @file   GameplayScene.h
 *
 * @brief  �Q�[���v���C�V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 */

#pragma once
#include "SceneBace.h"
#include <memory>
#include "StepTimer.h"
#include "GeometricPrimitive.h"
#include "SkyboxEffect.h"

#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"
#include "ImaseLib/DebugCamera.h"
#include "Camera.h"

/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
class GameplayScene final :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // �f�o�b�O�t�H���g
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // �O���b�h�̏�
    std::unique_ptr<Imase::GridFloor> m_gridFloor;

    // �f�o�b�O�J����
    std::unique_ptr<Imase::DebugCamera> m_DebugCamera;

	// �J����
    std::unique_ptr<Camera> m_Camera;

    // SkyBox
    std::unique_ptr<DirectX::GeometricPrimitive> m_sky;
    std::unique_ptr<SkyboxEffect> m_effect;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_skyInputLayout;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubemap;

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

