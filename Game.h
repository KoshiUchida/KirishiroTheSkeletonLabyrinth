//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "Managers/SceneManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();

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

    void OnNewAudioDevice() noexcept { m_retryAudio = true; }

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

    // �I�[�f�B�I�G���W��
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

    // �I�[�f�B�I�̃��g���C�t���O
    bool m_retryAudio;
 };
