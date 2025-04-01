/**
 * @file   BoxCollider.h
 *
 * @brief  ボックスコライダークラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include "ColliderBace.h"
#include "GeometricPrimitive.h"

// 前方宣言
class Transform;
class SceneBace;

/// <summary>
/// ボックスコライダークラス
/// </summary>
class BoxCollider :
    public ColliderBace
{
private:
	// サイズ
	DirectX::SimpleMath::Vector3 m_Siz;

	// 頂点の座標群
	Positions m_Positions;

public:
	/*Main System*/
	BoxCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, bool canDraw = true) noexcept(false);
	~BoxCollider() noexcept;

	bool IsHit(ColliderBace* other) override final;

	bool IsHit(const DirectX::SimpleMath::Vector3& other) override final;

	void Collision(ColliderBace* other) override final;

	/*Getter*/
	DirectX::SimpleMath::Vector3 GetSiz() const;
};

