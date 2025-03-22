#include <vector>

class SkyboxEffect : public DirectX::IEffect, public DirectX::IEffectMatrices
{
public:
    explicit SkyboxEffect(ID3D11Device* device);

    virtual void Apply(
        ID3D11DeviceContext* deviceContext) override;

    virtual void GetVertexShaderBytecode(
        void const** pShaderByteCode,
        size_t* pByteCodeLength) override;

    void SetTexture(ID3D11ShaderResourceView* value);
    void XM_CALLCONV SetWorld(DirectX::FXMMATRIX value) override;
    void XM_CALLCONV SetView(DirectX::FXMMATRIX value) override;
    void XM_CALLCONV SetProjection(DirectX::FXMMATRIX value) override;
    void XM_CALLCONV SetMatrices(DirectX::FXMMATRIX world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) override;

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
    std::vector<uint8_t> m_vsBlob;

    DirectX::SimpleMath::Matrix m_view;
    DirectX::SimpleMath::Matrix m_proj;
    DirectX::SimpleMath::Matrix m_worldViewProj;

    uint32_t m_dirtyFlags;

    struct __declspec(align(16)) SkyboxEffectConstants
    {
        DirectX::XMMATRIX worldViewProj;
    };

    DirectX::ConstantBuffer<SkyboxEffectConstants> m_constantBuffer;
};