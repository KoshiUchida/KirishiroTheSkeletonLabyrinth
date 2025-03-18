/**
 * @file   SphereCollider.h
 *
 * @brief  球コライダークラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */

#pragma once
#include "ColliderBace.h"

class Transform;
class SceneBace;

/// <summary>
/// 球コライダークラス
/// </summary>
class SphereCollider
	: public ColliderBace
{
private:
	// 半径
	float m_Radius;
	
public:
	/*Main System*/
	SphereCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, float radius, bool canDraw = true, const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3()) noexcept;
	~SphereCollider() noexcept;

	bool Collider(ColliderBace* other) override final;

	void Collision(ColliderBace* other) override final;

	/*Getter*/
	float GetRadius() const;
};

