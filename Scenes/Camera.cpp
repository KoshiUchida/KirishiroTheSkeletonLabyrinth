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

/*前方宣言*/
#include "../Components/Transform.h"

using namespace DirectX;

/*Main System*/

/// <summary>
/// Constructor
/// </summary>
/// <param name="_eye">視点の座標</param>
/// <param name="_target">注点の座標</param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, const DirectX::SimpleMath::Vector3& _target) noexcept
	: m_Eye   { _eye }
	, m_Target{ _target }
	, m_View{}
	, mp_Target{ nullptr }
{
}

/// <summary>
/// Destructor
/// </summary>
Camera::~Camera() noexcept = default;

/// <summary>
/// 
/// </summary>
/// <param name="_eye"></param>
/// <param name="pTarget"></param>
Camera::Camera(const DirectX::SimpleMath::Vector3& _eye, Transform* pTarget) noexcept
	: m_Eye    { _eye }
	, m_Target { SimpleMath::Vector3::Zero}
	, m_View   {}
	, mp_Target{ pTarget }
{
}

/// <summary>
/// 更新処理
/// </summary>
void Camera::Update()
{
	ViewUpdate();
}

/// <summary>
/// ビュー行列の更新処理
/// </summary>
void Camera::ViewUpdate()
{
	if (mp_Target)
	{
		m_View = SimpleMath::Matrix::CreateLookAt(mp_Target->GetPosition() + m_Eye, mp_Target->GetPosition(), SimpleMath::Vector3::UnitY);
	}
	else
	{
		m_View = SimpleMath::Matrix::CreateLookAt(m_Eye, m_Target, SimpleMath::Vector3::UnitY);
	}
}


/*Setter*/

/// <summary>
/// 視点の設定関数
/// </summary>
/// <param name="position">視点の座標</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Eye = position;
}

/// <summary>
/// 注点の設定関数
/// </summary>
/// <param name="position">注点の座標</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_Target = position;
}

/// <summary>
/// 注視点ポインタの設定関数
/// </summary>
/// <param name="pPosition">注視点となる座標へのポインタ</param>
void Camera::SetTargetPositionPtr(Transform* pPosition)
{
	mp_Target = pPosition;
}



/*Getter*/

/// <summary>
/// デバッグカメラのビュー行列の取得関数
/// </summary>
/// <returns>ビュー行列</returns>
DirectX::SimpleMath::Matrix Camera::GetCameraMatrix()
{
	return m_View;
}

/// <summary>
/// カメラの位置の取得関数
/// </summary>
/// <returns>視点の位置</returns>
DirectX::SimpleMath::Vector3 Camera::GetEyePosition()
{
	return m_Eye;
}


/// <summary>
/// デバッグカメラの注視点の取得関数
/// </summary>
/// <returns>注視点の位置</returns>
DirectX::SimpleMath::Vector3 Camera::GetTargetPosition()
{
	return m_Target;
}

