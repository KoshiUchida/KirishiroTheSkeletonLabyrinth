/**
 * @file   ColliderBace.h
 *
 * @brief  コライダー基底クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ComponentsBace.h"
#include "GeometricPrimitive.h"
#include "DeviceResources.h"

// 前方宣言
class SceneBace;
class Transform;

/// <summary>
/// コライダー基底クラス
/// </summary>
class ColliderBace:
	public ComponentsBace
{
protected:
	// コライダータイプの全種
	enum class ColliderType
	{
		Sphare,
		Box,
	};

	// コライダータイプ
	ColliderType m_Type;
	
	// 中心となるトランスフォームへのポインタ
	Transform* mp_Transform;

	// 描画の許可
	bool m_CanDraw;

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
	ColliderBace(SceneBace* pScene, ColliderType type, const std::string& name, Transform* pTransform, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false);
	virtual ~ColliderBace() noexcept;

	void Render(const DirectX::SimpleMath::Matrix& view);

	virtual bool IsHit(ColliderBace* other) = 0;

	virtual bool IsHit(const DirectX::SimpleMath::Vector3& other) = 0;

	virtual void Collision(ColliderBace* other) = 0;

	/*Setter*/
	void CanDraw(bool can) { m_CanDraw = can; }

	void SetOffset(const DirectX::SimpleMath::Vector3& offset);

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetPosition() const;
	                ColliderType GetType()     const { return m_Type; }

protected:
	// 頂点の座標群構造体
	struct Positions
	{
		DirectX::SimpleMath::Vector3 max;
		DirectX::SimpleMath::Vector3 min;
		DirectX::SimpleMath::Vector3 p1;
		DirectX::SimpleMath::Vector3 p2;
		DirectX::SimpleMath::Vector3 p3;
		DirectX::SimpleMath::Vector3 p4;
		DirectX::SimpleMath::Vector3 p5;
		DirectX::SimpleMath::Vector3 p6;
	};

	// 頂点の座標群への入力
	void AddSiz(Positions* pPositions, const DirectX::SimpleMath::Vector3& addSiz);

	// 頂点座標群の移動
	void MovePositions(Positions* pPositions, const DirectX::SimpleMath::Vector3& move);
};

