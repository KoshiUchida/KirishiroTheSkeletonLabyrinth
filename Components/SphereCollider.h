/**
 * @file   SphereCollider.h
 *
 * @brief  球コライダークラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/10
 */

#pragma once
#include "ComponentsBace.h"
#include "DeviceResources.h"
#include "GeometricPrimitive.h"

class Transform;
class SceneBace;

/// <summary>
/// 球コライダークラス
/// </summary>
class SphereCollider
	: public ComponentsBace
{
private:
	// 中心座標となる座標へのポインタ
	Transform* mp_Transform;

	// 半径
	float m_Radius;

	// オフセット
	DirectX::SimpleMath::Vector3 m_Offset;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// デバッグ表示
	std::unique_ptr<DirectX::DX11::GeometricPrimitive> m_Model;
	
public:
	/*Main System*/
	SphereCollider(const std::string& name, Transform* pTransform, float radius, SceneBace* pScene, const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3()) noexcept;
	~SphereCollider() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	bool Collider(const SphereCollider& other);

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;
	float GetRadius() const;
};

