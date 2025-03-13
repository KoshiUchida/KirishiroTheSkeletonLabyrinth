/**
 * @file   BoxCollider.h
 *
 * @brief  ボックスコライダークラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */

#pragma once
#include "ComponentsBace.h"
#include "DeviceResources.h"
#include "GeometricPrimitive.h"

// 前方宣言
class Transform;
class SceneBace;

/// <summary>
/// ボックスコライダークラス
/// </summary>
class BoxCollider :
    public ComponentsBace
{
private:
	// 中心座標となる座標へのポインタ
	Transform* mp_Transform;

	// サイズ
	DirectX::SimpleMath::Vector3 m_Siz;

	// オフセット
	DirectX::SimpleMath::Vector3 m_Offset;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// デバッグ表示
	std::unique_ptr<DirectX::DX11::GeometricPrimitive> m_Model;

	// 表示設定
	bool m_CanDraw;

public:
	/*Main System*/
	BoxCollider(const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, SceneBace* pScene, bool canDraw = true, const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3()) noexcept(false);
	~BoxCollider() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	bool Collider(const BoxCollider& other);

	/*Setter*/
	void CanDraw(bool can) { m_CanDraw = can; }

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;

	DirectX::SimpleMath::Vector3 GetSiz() const;
};

