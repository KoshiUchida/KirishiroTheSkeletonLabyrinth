/**
 * @file   SphereCollider.cpp
 *
 * @brief  球コライダークラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#include "pch.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
/// <param name="pTransform">中心座標となるトランスフォームへのポインタ</param>
/// <param name="radius">半径</param>
/// <param name="offset">オフセット</param>
SphereCollider::SphereCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, float radius, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept
	: ColliderBace(pScene, ColliderType::Sphare, name, pTransform, canDraw, offset)
	, m_Radius{ radius }
{
#if defined(_DEBUG)
	m_Model = GeometricPrimitive::CreateSphere(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext(), m_Radius * 2.f);
#endif
}

/// <summary>
/// Destructor
/// </summary>
SphereCollider::~SphereCollider() noexcept = default;

/// <summary>
/// 重なり判定
/// </summary>
/// <param name="other">重なりを調べるコライダー</param>
bool SphereCollider::IsHit(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Sphare:
		if (true)
		{
			// 重なる距離を求める
			float radiusSum = this->GetRadius() + static_cast<SphereCollider*>(other)->GetRadius();

			// コライダー同士の距離を求める
			SimpleMath::Vector3 positionA = this->GetPosition();
			SimpleMath::Vector3 positionB = other->GetPosition();
			float x = positionB.x - positionA.x;
			float y = positionB.y - positionA.y;
			float z = positionB.z - positionA.z;
			float intersect = sqrtf(x * x + y * y + z * z);

			// コライダーの重なりを調べる
			return intersect <= radiusSum;
		}
	case ColliderType::Box:
		if (true)
		{
		}
	default:
		return false;
	}
}

void SphereCollider::Collision(ColliderBace* other)
{
	other;

	// ToDo:押し出し処理
}

/// <summary>
/// 半径の取得
/// </summary>
/// <returns>半径</returns>
float SphereCollider::GetRadius() const
{
	return m_Radius;
}
