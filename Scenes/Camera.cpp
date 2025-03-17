/**
 * @file   Camera.h
 *
 * @brief  カメラクラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */
#include "pch.h"
#include "Camera.h"

using namespace DirectX;

/*Main System*/

/// <summary>
/// Constructor
/// </summary>
/// <param name="_eye">視点の座標</param>
/// <param name="_target">注点の座標</param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, const DirectX::SimpleMath::Vector3& _target)
	: m_eye   { _eye }
	, m_target{ _target }
	, m_view{}
{
	ViewUpdate();
}

/// <summary>
/// ビュー行列の更新処理
/// </summary>
void Camera::ViewUpdate()
{
	m_view = SimpleMath::Matrix::CreateLookAt(m_eye, m_target, SimpleMath::Vector3::UnitY);
}


/*Setter*/

/// <summary>
/// 視点の設定関数
/// </summary>
/// <param name="position">視点の座標</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_eye = position;

	ViewUpdate();
}

/// <summary>
/// 注点の設定関数
/// </summary>
/// <param name="position">注点の座標</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_target = position;

	ViewUpdate();
}



/*Getter*/

/// <summary>
/// デバッグカメラのビュー行列の取得関数
/// </summary>
/// <returns>ビュー行列</returns>
DirectX::SimpleMath::Matrix Camera::GetCameraMatrix()
{
	return m_view;
}

/// <summary>
/// カメラの位置の取得関数
/// </summary>
/// <returns>視点の位置</returns>
DirectX::SimpleMath::Vector3 Camera::GetEyePosition()
{
	return m_eye;
}


/// <summary>
/// デバッグカメラの注視点の取得関数
/// </summary>
/// <returns>注視点の位置</returns>
DirectX::SimpleMath::Vector3 Camera::GetTargetPosition()
{
	return m_target;
}

