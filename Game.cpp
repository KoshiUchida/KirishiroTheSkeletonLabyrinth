//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "DDSTextureLoader.h"

#include "Scenes/GameplayScene.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false) :
    m_pitch(0),
    m_yaw(0)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    srand(static_cast<unsigned int>(time(NULL)));

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    //m_gamePad = std::make_unique<GamePad>();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // シーンマネージャの更新
    m_sceneManager->Update(elapsedTime);

    // Skyboxの更新処理

    // キーボードの入力を取得
    Keyboard::State kd = Keyboard::Get().GetState();

    if (kd.U)
    {
        m_yaw = m_pitch = 0.f;
    }
    else
    {
        constexpr float ROTATION_GAIN = 0.1f;
        if (kd.L)
        {
            m_yaw += -1.f * ROTATION_GAIN;
        }
        if (kd.J)
        {
            m_yaw += 1.f * ROTATION_GAIN;
        }
        if (kd.I)
        {
            m_pitch += 1.f * ROTATION_GAIN;
        }
        if (kd.K)
        {
            m_pitch += -1.f * ROTATION_GAIN;
        }
    }

    // limit pitch to straight up or straight down
    constexpr float limit = XM_PIDIV2 - 0.01f;
    m_pitch = std::max(-limit, m_pitch);
    m_pitch = std::min(+limit, m_pitch);

    // keep longitude in sane range by wrapping
    if (m_yaw > XM_PI)
    {
        m_yaw -= XM_2PI;
    }
    else if (m_yaw < -XM_PI)
    {
        m_yaw += XM_2PI;
    }

    float y = sinf(m_pitch);
    float r = cosf(m_pitch);
    float z = r * cosf(m_yaw);
    float x = r * sinf(m_yaw);

    XMVECTORF32 lookAt = { x, y, z, 0.f };
    m_view = XMMatrixLookAtRH(g_XMZero, lookAt, SimpleMath::Vector3::Up);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();
    m_deviceResources->PIXBeginEvent(L"Render");

    // Skyboxの描画処理
    m_effect->SetView(m_view);
    m_sky->Draw(m_effect.get(), m_skyInputLayout.Get());

    // シーンマネージャの描画処理
    m_sceneManager->Render();


    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
    //m_gamePad->Resume();
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
    //m_gamePad->Suspend();
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    //m_gamePad->Suspend();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    //m_gamePad->Resume();
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    m_sky = GeometricPrimitive::CreateGeoSphere(context, 2.f, 3,
        false /*invert for bein inside the shape*/);

    m_effect = std::make_unique<SkyboxEffect>(device);

    m_sky->CreateInputLayout(m_effect.get(),
        m_skyInputLayout.ReleaseAndGetAddressOf());

    DX::ThrowIfFailed(
        CreateDDSTextureFromFile(device, L"lobbycube.dds",
            nullptr, m_cubemap.ReleaseAndGetAddressOf()));

    m_effect->SetTexture(m_cubemap.Get());

    // 共通ステートの作成
    m_states = std::make_unique<CommonStates>(device);

    // ベーシックエフェクトの作成
    m_basicEffect = std::make_unique<BasicEffect>(device);
    // ライト(OFF)
    m_basicEffect->SetLightingEnabled(false);
    // 頂点カラー(OFF)
    m_basicEffect->SetVertexColorEnabled(false);
    // テクスチャ(ON)
    m_basicEffect->SetTextureEnabled(true);

    // アルファテストエフェクトの作成
    m_alphaTestEffect = std::make_unique<AlphaTestEffect>(device);
    m_alphaTestEffect->SetAlpha(200);

    // 入力レイアウトの作成
    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionTexture>(
            device, m_basicEffect.get(), m_inputLayout.ReleaseAndGetAddressOf())
    );

    // プリミティブバッチの作成
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

    // シーンマネージャの作成
    m_sceneManager = std::make_unique<SceneManager>();

    // シーンの登録
    m_sceneManager->addScene(
        "Gameplay",
        std::make_unique<GameplayScene>(
            m_sceneManager.get(),
            m_deviceResources.get(),
            &m_proj,
            m_states.get(),
            &m_timer
        )
    );

    // 最初のシーンを設定
#if defined(_DEBUG)
    m_sceneManager->SetStartScene("Gameplay");
#else
    m_sceneManager->SetStartScene("Gameplay");
#endif
 }

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

    //// 画面サイズの取得
    //RECT rect = m_deviceResources->GetOutputSize();

    //// 射影行列の作成
    //m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
    //    XMConvertToRadians(45.0f)
    //    , static_cast<float>(rect.right) / static_cast<float>(rect.bottom)
    //    , 0.1f, 100.0f);

    auto size = m_deviceResources->GetOutputSize();

    m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
        float(size.right) / float(size.bottom), 0.1f, 10.f);

    m_effect->SetProjection(m_proj);

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_sky.reset();
    m_effect.reset();
    m_skyInputLayout.Reset();
    m_cubemap.Reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
