/**
 * @file   Camera.h
 *
 * @brief  カメラクラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#pragma once

/*前方宣言*/
class Transform;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
private:
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_View;

	// 視点
	DirectX::SimpleMath::Vector3 m_Eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_Target;

	// 注視点となる座標へのポインタ
	Transform* mp_Target;

public:
	/*Main System*/

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		const DirectX::SimpleMath::Vector3& _target = DirectX::SimpleMath::Vector3::Zero
	) noexcept;

	~Camera() noexcept;

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		Transform* pTarget
	) noexcept;

	void Update();

	void ViewUpdate();

	/*Setter*/

	void SetEyePosition   (const DirectX::SimpleMath::Vector3& position);

	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);

	void SetTargetPositionPtr(Transform* pPosition);

	/*Getter*/

	DirectX::SimpleMath::Matrix GetCameraMatrix();

	DirectX::SimpleMath::Vector3 GetEyePosition();

	DirectX::SimpleMath::Vector3 GetTargetPosition();
};

