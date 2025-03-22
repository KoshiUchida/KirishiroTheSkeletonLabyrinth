#include <vector>

class SkyboxEffect : public DirectX::IEffect
{
public:
    explicit SkyboxEffect(ID3D11Device* device);

    virtual void Apply(
        ID3D11DeviceContext* deviceContext) override;

    virtual void GetVertexShaderBytecode(
        void const** pShaderByteCode,
        size_t* pByteCodeLength) override;

    void SetTexture(ID3D11ShaderResourceView* value);

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
    std::vector<uint8_t> m_vsBlob;
};