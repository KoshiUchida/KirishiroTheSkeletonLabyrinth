/**
 * @file   Renderer2D.h
 *
 * @brief  �Q���������_���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "RendererBace.h"

#include "DeviceResources.h"

// �O���錾
class SceneBace;
class Transform2D;

class Renderer2D :
    public RendererBace
{
private:
    // �g�����X�t�H�[���ւ̃|�C���^
    Transform2D* mp_Transform;

    // �f�o�C�X���\�[�X�ւ̃|�C���^
    DX::DeviceResources* mp_DeviceResources;

    // �X�v���C�g�o�b�`
    std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    // �e�N�X�`��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;

    // �e�N�X�`���̒��S���W
    DirectX::SimpleMath::Vector2 m_Origin;

    // �e�N�X�`���̓����x
    float m_Alpha;

    // �I�t�Z�b�g
    DirectX::SimpleMath::Vector2 m_Offset;

public:
    /*Main System*/
    Renderer2D(SceneBace* pScene, const std::string& name, Transform2D* pTransform, const wchar_t* modelPath) noexcept;
    ~Renderer2D() noexcept;

    void Draw(const DirectX::SimpleMath::Matrix& view) override final;

    // Setter
    void SetOrigin(DirectX::SimpleMath::Vector2 origin);
    void SetAlpha(float alpha);
    void SetOffset(DirectX::SimpleMath::Vector2 offset);
};

