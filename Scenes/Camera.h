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

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
private:
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

public:
	/*Main System*/

	Camera(
		const DirectX::SimpleMath::Vector3& _eye,
		const DirectX::SimpleMath::Vector3& _target = DirectX::SimpleMath::Vector3::Zero
	);

	void ViewUpdate();

	/*Setter*/

	void SetEyePosition   (const DirectX::SimpleMath::Vector3& position);

	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);

	/*Getter*/

	DirectX::SimpleMath::Matrix GetCameraMatrix();

	DirectX::SimpleMath::Vector3 GetEyePosition();

	DirectX::SimpleMath::Vector3 GetTargetPosition();
};

