//--------------------------------------------------------------------------------------
// File: DebugFont.h
//
// デバッグ用文字フォント描画クラス
//
// Usage: DebugFontクラスは2D版、DebugFont3Dクラスは3D版です。
//        AddString関数で文字列を登録します。登録された情報は描画後クリアされます。
//        デバッグ用の文字列の表示などに使用してください。
//		  ※デバッグ用なので深度バッファはみていません。（必ず描画される）
//
// Date: 2023.3.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <vector>
#include <string>

namespace Imase
{

	class DebugFont
	{
	private:

		// 文字列情報
		struct String
		{
			// 位置
			DirectX::SimpleMath::Vector2 pos;

			// 文字列
			std::wstring string;

			// 色
			DirectX::SimpleMath::Color color;

			// スケール
			float scale = 1.0f;
		};

		// 表示文字列の配列
		std::vector<String> m_strings;

	protected:

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

		// フォントの縦サイズ
		float m_fontHeight;

	public:

		// コンストラクタ
		DebugFont(ID3D11Device* device, ID3D11DeviceContext* context, wchar_t const* fileName);

		// デストラクタ
		virtual ~DebugFont();

		// 描画する文字列を登録する関数
		template <class... Args>
		void AddString(int x, int y, const DirectX::FXMVECTOR& color, const wchar_t* format, const Args& ... args)
		{
			int textLength = std::swprintf(nullptr, 0, format, args ...);
			if (textLength < 0)
			{
				throw std::runtime_error("String Formatting Error.");
			}

			size_t bufferSize = textLength + sizeof(L'\0');
			std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(bufferSize);
			std::swprintf(buffer.get(), bufferSize, format, args ...);

			AddString(buffer.get(), DirectX::SimpleMath::Vector2{ static_cast<float>(x),static_cast<float>(y) }, color);
		}

		// 描画する文字列を登録する関数
		void AddString(
			const wchar_t* string,
			DirectX::SimpleMath::Vector2 pos,
			DirectX::FXMVECTOR color = DirectX::Colors::White,
			float scale = 1.0f);

		// 描画関数
		void Render(DirectX::CommonStates* states);

		// フォントの高さを取得する関数
		float GetFontHeight() {	return m_fontHeight; }
	};

	class DebugFont3D : protected DebugFont
	{
	private:

		// 文字列情報
		struct String
		{
			// 位置
			DirectX::SimpleMath::Vector3 pos;

			// 文字列
			std::wstring string;

			// 色
			DirectX::SimpleMath::Color color;

			// スケール
			float scale = 1.0f;
		};

		// 表示文字列の配列
		std::vector<String> m_strings;

		// エフェクト
		std::unique_ptr<DirectX::BasicEffect> m_effect;

		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	public:

		// コンストラクタ
		DebugFont3D(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			wchar_t const* fileName);

		// デストラクタ
		~DebugFont3D();

		// 描画する文字列を登録する関数
		template <class... Args>
		void AddString(DirectX::SimpleMath::Vector3 pos, const DirectX::FXMVECTOR& color, const wchar_t* format, const Args& ... args)
		{
			int textLength = std::swprintf(nullptr, 0, format, args ...);
			if (textLength < 0)
			{
				throw std::runtime_error("String Formatting Error.");
			}

			size_t bufferSize = textLength + sizeof(L'\0');
			std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(bufferSize);
			std::swprintf(buffer.get(), bufferSize, format, args ...);

			AddString(buffer.get(), pos, color);
		}

		// 描画する文字列を登録する関数
		void AddString(
			const wchar_t* string,
			DirectX::SimpleMath::Vector3 pos,
			DirectX::FXMVECTOR color = DirectX::Colors::White,
			float scale = 1.0f);

		// 描画関数
		void Render(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj);

		// フォントの高さを取得する関数
		float GetFontHeight() { return m_fontHeight; }
	};

}

