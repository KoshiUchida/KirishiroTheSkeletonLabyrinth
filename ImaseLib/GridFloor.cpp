//--------------------------------------------------------------------------------------
// File: GridFloor.cpp
//
// グリッドの床を描画するクラス
//
// Date: 2023.5.6
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "GridFloor.h"
#include "DebugDraw.h"

using namespace DirectX;
using namespace Imase;

// 床の1辺のサイズ
const  float GridFloor::FLOOR_SIZE = 10.0f;

GridFloor::GridFloor(
	ID3D11Device* pDevice,
	ID3D11DeviceContext* pContext,
	CommonStates* pStates,
	FXMVECTOR color,
	float size,
	size_t divs
)
	: m_pStates(pStates)
	, m_color(color)
	, m_size(size)
	, m_divs(divs)
{
	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(pContext);

	// ベーシックエフェクトの作成
	m_basicEffect = std::make_unique<BasicEffect>(pDevice);
	m_basicEffect->SetVertexColorEnabled(true);
	m_basicEffect->SetLightingEnabled(false);
	m_basicEffect->SetTextureEnabled(false);

	// 入力レイアウトの作成
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			pDevice,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
			)
	);
}

void GridFloor::Render(
	ID3D11DeviceContext* pContext,
	const SimpleMath::Matrix& view,
	const SimpleMath::Matrix& proj
)
{
	// ブレンドステートの設定（不透明）
	pContext->OMSetBlendState(m_pStates->Opaque(), nullptr, 0xFFFFFFFF);
	// 深度バッファの設定（通常）
	pContext->OMSetDepthStencilState(m_pStates->DepthDefault(), 0);
	// カリングの設定（カリングなし）
	pContext->RSSetState(m_pStates->CullNone());

	// 各行列の設定
	SimpleMath::Matrix world;
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	// エフェクトを適用する
	m_basicEffect->Apply(pContext);

	// 入力レイアウトを設定
	pContext->IASetInputLayout(m_inputLayout.Get());

	// グリッドの床を描画
	m_primitiveBatch->Begin();

	DX::DrawGrid(
		m_primitiveBatch.get(),
		SimpleMath::Vector3(m_size / 2.0f, 0.0f, 0.0f),
		SimpleMath::Vector3(0.0f, 0.0f, m_size / 2.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		m_divs, m_divs,
		m_color
	);

	m_primitiveBatch->End();
}
