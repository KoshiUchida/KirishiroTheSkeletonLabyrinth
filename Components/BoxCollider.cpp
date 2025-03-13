/**
 * @file   BoxCollider.cpp
 *
 * @brief  ボックスコライダークラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/13
 */

#include "pch.h"
#include "BoxCollider.h"

// 前方宣言
#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
BoxCollider::BoxCollider(const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, SceneBace* pScene, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false)
	: ComponentsBace(ComponentsBace::Tags::Collider, name)
	, mp_Transform       { pTransform }
	, m_Offset           { offset }
	, m_Siz              { siz }
	, mp_DeviceResources { pScene->GetDeviceResourcesPointer() }
	, mp_Proj            { pScene->GetProjPointer() }
	, m_CanDraw          { canDraw }
{
	m_Model = GeometricPrimitive::CreateBox(mp_DeviceResources->GetD3DDeviceContext(), siz);
}

/// <summary>
/// Destructor
/// </summary>
BoxCollider::~BoxCollider() noexcept = default;

/// <summary>
/// 描画処理
/// </summary>
void BoxCollider::Render(const DirectX::SimpleMath::Matrix& view)
{
	if (!m_CanDraw)
		return;

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
bool BoxCollider::Collider(const BoxCollider& other)
{
	return false;
}

/// <summary>
/// 座標の取得
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// サイズの取得
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetSiz() const
{
	return m_Siz;
}
