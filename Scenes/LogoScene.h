/**
 * @file   LogoScene.h
 *
 * @brief  ���S�V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 */

#pragma once
#include "SceneBace.h"

#include <memory>
#include "StepTimer.h"

#if defined(_DEBUG)
 // �f�o�b�O�K�{�ǂݍ���
#include "ImaseLib/DebugFont.h"

#endif

 // �O���錾
class Camera;

/// <summary>
/// ���S�V�[���N���X
/// </summary>
class LogoScene :
    public SceneBace
{
private:
    DX::StepTimer* mp_timer;

    // �J����
    std::unique_ptr<Camera> m_Camera;

    // �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    // ���݂̌o�ߎ���
    float m_Time;

    // ��ʂ̃T�C�Y
	RECT m_FullscreenRect;



	// ���S�̃e�N�X�`��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture_Logo;

    // ���S�e�N�X�`���̃I���W��
    DirectX::SimpleMath::Vector2 m_LogoOrigin;

    // ���S�e�N�X�`���̍��W
    DirectX::SimpleMath::Vector2 m_LogoPos;

    // ���S�̓����x
	float m_LogoAlpha;



	// �w�i�̃e�N�X�`��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture_Background;

#if defined(_DEBUG)
    /*�f�o�b�O�p�X�}�[�g�|�C���^*/
    // �f�o�b�O�t�H���g
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

