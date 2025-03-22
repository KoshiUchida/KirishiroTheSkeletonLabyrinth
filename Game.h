//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "GeometricPrimitive.h"
#include "GamePad.h"
#include "SkyboxEffect.h"

#include "Managers/SceneManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // �ˉe�s��
    DirectX::SimpleMath::Matrix m_proj;

    // ���ʃX�e�[�g
    std::unique_ptr<DirectX::CommonStates> m_states;

    // �x�[�V�b�N�G�t�F�N�g
    std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

    // �A���t�@�e�X�g�G�t�F�N�g
    std::unique_ptr<DirectX::AlphaTestEffect> m_alphaTestEffect;

    // ���̓��C�A�E�g
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    // �v���~�e�B�u�o�b�`
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

    // �V�[���}�l�[�W��
    std::unique_ptr<SceneManager> m_sceneManager;

    // Skybox
    //std::unique_ptr<DirectX::GamePad> m_gamePad;
    DirectX::SimpleMath::Matrix m_view;
    //DirectX::SimpleMath::Matrix m_proj;

    float m_pitch;
    float m_yaw;

    std::unique_ptr<DirectX::GeometricPrimitive> m_sky;
    std::unique_ptr<SkyboxEffect> m_effect;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_skyInputLayout;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubemap;
 };
