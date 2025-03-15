/**
 * @file   ColliderBace.cpp
 *
 * @brief  コライダー基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/15
 */

#include "pch.h"
#include "ColliderBace.h"

// 前方宣言
#include "../Scenes/SceneBace.h"
#include "../Components/Transform.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
ColliderBace::ColliderBace(SceneBace* pScene, ColliderType type, const std::string& name, Transform* pTransform, bool canDraw, const DirectX::SimpleMath::Vector3& offset) noexcept(false)
	: ComponentsBace(ComponentsBace::Tags::Collider, name)
	, mp_Transform{ pTransform }
	, m_Type      { type }
	, m_CanDraw   { canDraw }
	, m_Offset    { offset }
	, mp_Proj           { nullptr }
	, mp_DeviceResources{ nullptr }
{
#if defined(_DEBUG)
	mp_Proj            = pScene->GetProjPointer();
	mp_DeviceResources = pScene->GetDeviceResourcesPointer();
#endif
}

/// <summary>
/// Destructor
/// </summary>
ColliderBace::~ColliderBace() noexcept = default;

void ColliderBace::Render(const DirectX::SimpleMath::Matrix& view)
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
/// 座標の取得
/// </summary>
DirectX::SimpleMath::Vector3 ColliderBace::GetPosition() const
{
	return mp_Transform->GetPosition() + m_Offset;
}

/// <summary>
/// 座標群への入力
/// </summary>
/// <param name="pPositions">入力する座標群へのポインタ</param>
/// <param name="addSiz">入力サイズ</param>
void ColliderBace::AddSiz(Positions* pPositions, const DirectX::SimpleMath::Vector3& addSiz)
{
	pPositions->max += addSiz;
	pPositions->min -= addSiz;

	pPositions->p1.x += addSiz.x;
	pPositions->p2.y += addSiz.y;
	pPositions->p3.z += addSiz.z;
}
