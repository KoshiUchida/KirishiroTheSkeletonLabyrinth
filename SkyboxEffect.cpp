#include "pch.h"
#include "SkyboxEffect.h"
#include "ReadData.h"

SkyboxEffect::SkyboxEffect(
    ID3D11Device* device)
{
    m_vsBlob = DX::ReadData(L"SkyboxEffect_VS.cso");

    DX::ThrowIfFailed(
        device->CreateVertexShader(m_vsBlob.data(), m_vsBlob.size(),
            nullptr, m_vs.ReleaseAndGetAddressOf()));

    auto psBlob = DX::ReadData(L"SkyboxEffect_PS.cso");

    DX::ThrowIfFailed(
        device->CreatePixelShader(psBlob.data(), psBlob.size(),
            nullptr, m_ps.ReleaseAndGetAddressOf()));
}

void SkyboxEffect::Apply(
    ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

    deviceContext->VSSetShader(m_vs.Get(), nullptr, 0);
    deviceContext->PSSetShader(m_ps.Get(), nullptr, 0);
}

void SkyboxEffect::GetVertexShaderBytecode(
    void const** pShaderByteCode,
    size_t* pByteCodeLength)
{
    assert(pShaderByteCode != nullptr && pByteCodeLength != nullptr);
    *pShaderByteCode = m_vsBlob.data();
    *pByteCodeLength = m_vsBlob.size();
}

void SkyboxEffect::SetTexture(
    ID3D11ShaderResourceView* value)
{
    m_texture = value;
}