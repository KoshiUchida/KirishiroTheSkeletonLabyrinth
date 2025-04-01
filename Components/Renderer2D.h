/**
 * @file   Renderer2D.h
 *
 * @brief  ２次元レンダラーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "RendererBace.h"

#include "DeviceResources.h"

// 前方宣言
class SceneBace;
class Transform2D;

class Renderer2D :
    public RendererBace
{
private:
    // トランスフォームへのポインタ
    Transform2D* mp_Transform;

    // デバイスリソースへのポインタ
    DX::DeviceResources* mp_DeviceResources;

    // スプライトバッチ
    std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    // テクスチャ
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;

    // テクスチャの中心座標
    DirectX::SimpleMath::Vector2 m_Origin;

    // テクスチャの透明度
    float m_Alpha;

    // オフセット
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

