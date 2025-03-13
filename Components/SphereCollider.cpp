
/**
 * @file   SphereCollider.cpp
 *
 * @brief  球コライダークラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/10
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
SphereCollider::SphereCollider(const std::string& name, Transform* pTransform, float radius, SceneBace* pScene, const DirectX::SimpleMath::Vector3& offset) noexcept
	: ComponentsBace(Tags::Collider, name)
	, mp_Transform{ pTransform }
	, m_Radius    { radius }
	, m_Offset    { offset }
{
	mp_DeviceResources = pScene->GetDeviceResourcesPointer();
	mp_Proj = pScene->GetProjPointer();
	m_Model = GeometricPrimitive::CreateSphere(pScene->GetDeviceResourcesPointer()->GetD3DDeviceContext(), m_Radius * 2.f);
}

/// <summary>
/// Destructor
/// </summary>
SphereCollider::~SphereCollider() noexcept
{
	mp_Transform       = nullptr;
	mp_DeviceResources = nullptr;
	mp_Proj            = nullptr;
	m_Model.reset();
}

/// <summary>
/// 描画処理
/// </summary>
void SphereCollider::Render(const DirectX::SimpleMath::Matrix& view)
{
#if defined(_DEBUG)
	// ワールド行列
	SimpleMath::Matrix world;

	// 平行移動する行列を作成する
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X軸で回転する行列を作成する
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y軸で回転する行列を作成する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z軸で回転する行列を作成する
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateZ());

	// 拡大する行列を作成する
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ワールド行列へ統合
	world = trans * rotZ * rotY * rotX * scale;

	m_Model->Draw(world, view, *mp_Proj);
#endif
}

/// <summary>
/// 重なり判定
/// </summary>
/// <param name="other">重なりを調べるコライダー</param>
bool SphereCollider::Collider(const SphereCollider& other)
{
	// 重なる距離を求める
	float radiusSum = this->GetRadius() + other.GetRadius();

	// コライダー同士の距離を求める
	SimpleMath::Vector3 positionA = this->GetPosition();
	SimpleMath::Vector3 positionB = other.GetPosition();
	float x = positionB.x - positionA.x;
	float y = positionB.y - positionA.y;
	float z = positionB.z - positionA.z;
	float intersect = sqrtf(x * x + y * y + z * z);

	// コライダーの重なりを調べる
	return intersect <= radiusSum;
}

/// <summary>
/// 中心座標の取得
/// </summary>
/// <returns>中心座標</returns>
DirectX::SimpleMath::Vector3 SphereCollider::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// 半径の取得
/// </summary>
/// <returns>半径</returns>
float SphereCollider::GetRadius() const
{
	return m_Radius;
}
