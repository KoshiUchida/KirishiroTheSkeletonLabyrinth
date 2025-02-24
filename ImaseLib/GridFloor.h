//--------------------------------------------------------------------------------------
// File: GridFloor.h
//
// グリッドの床を描画するクラス
//
// Date: 2023.5.6
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

namespace Imase
{
	// グリッドの床を表示するタスク
	class GridFloor
	{
	public:

		// コンストラクタ
		GridFloor(
			ID3D11Device* pDevice,
			ID3D11DeviceContext* pContext,
			DirectX::CommonStates* pStates,
			DirectX::FXMVECTOR color = DirectX::Colors::LightGray,
			float size = FLOOR_SIZE,
			size_t divs = FLOOR_DIVS
		);

		// 描画
		void Render(
			ID3D11DeviceContext* pContext,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj
		);

	private:

		// 共通ステートへのポインタ
		DirectX::CommonStates* m_pStates;

		// ベーシックエフェクトへのポインタ
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

		// プリミティブバッチへのポインタ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// サイズ
		float m_size;

		// 分割数
		size_t m_divs;

		// 表示色
		DirectX::SimpleMath::Color m_color;

	public:

		// 床の1辺のサイズ
		static const float FLOOR_SIZE;

		// 分割数
		static const size_t FLOOR_DIVS = 10;

		// 床の１辺のサイズを変更する関数
		void SetSize(float size) { m_size = size; }

		// 床の分割数を変更する関数
		void SetDivs(size_t divs) { m_divs = divs; }

		// 色を設定する関数
		void SetColor(DirectX::FXMVECTOR color) { m_color = color; }

	};
}
