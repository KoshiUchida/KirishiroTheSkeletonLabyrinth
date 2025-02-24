//--------------------------------------------------------------------------------------
// File: DebugCamera.h
//
// デバッグ用カメラクラス
//
// Date: 2018.4.15
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

namespace Imase
{

	// デバッグ用カメラクラス
	class DebugCamera
	{
		// カメラの距離
		static const float DEFAULT_CAMERA_DISTANCE;

		// 横回転
		float m_yAngle, m_yTmp;

		// 縦回転
		float m_xAngle, m_xTmp;

		// ドラッグされた座標
		int m_x, m_y;

		float m_sx, m_sy;

		// 生成されたビュー行列
		DirectX::SimpleMath::Matrix m_view;

		// スクロールフォイール値
		int m_scrollWheelValue;

		// 視点
		DirectX::SimpleMath::Vector3 m_eye;

		// 注視点
		DirectX::SimpleMath::Vector3 m_target;

		// マウストラッカー
		DirectX::Mouse::ButtonStateTracker m_tracker;

		// スクリーンサイズ
		int m_screenW, m_screenH;

	private:

		void Motion(int x, int y);

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="windowWidth">ウインドウサイズ（幅）</param>
		/// <param name="windowHeight">ウインドウサイズ（高さ）</param>
		DebugCamera(int windowWidth, int windowHeight);

		/// <summary>
		/// デバッグカメラの更新
		/// </summary>
		/// <param name="mouse">マウスオブジェクトへのポインタ</param>
		void Update();

		/// <summary>
		/// デバッグカメラのビュー行列の取得関数
		/// </summary>
		/// <returns>ビュー行列</returns>
		DirectX::SimpleMath::Matrix GetCameraMatrix();

		/// <summary>
		/// デバッグカメラの位置の取得関数
		/// </summary>
		/// <returns>視点の位置</returns>
		DirectX::SimpleMath::Vector3 GetEyePosition();

		/// <summary>
		/// デバッグカメラの注視点の取得関数
		/// </summary>
		/// <returns>注視点の位置</returns>
		DirectX::SimpleMath::Vector3 GetTargetPosition();

		/// <summary>
		/// 画面サイズの設定関数
		/// </summary>
		/// <param name="windowWidth">ウインドウサイズ（幅）</param>
		/// <param name="windowHeight">ウインドウサイズ（高さ）</param>
		void SetWindowSize(int windowWidth, int windowHeight);

		/// <summary>
		/// 画面サイズの取得関数
		/// </summary>
		void GetWindowSize(int& windowWidth, int& windowHeight);
	};

}
