/**
 * @file   Renderer3D.cpp
 *
 * @brief  モデル描画コンポーネントのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#include "pch.h"
#include "Renderer3D.h"

#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

Renderer3D::Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false)
	: mp_Transform{ pTransform }
	, mp_DeviceResources{ pScene->GetDeviceResourcesPointer() }
	, mp_Proj{ pScene->GetProjPointer() }
	, mp_States{ pScene->GetCommonStatesPointer() }
{
	// モデルの読み込み
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
		device, modelPath, fx);
}

Renderer3D::~Renderer3D() noexcept
{
	m_Model.reset();
}

void Renderer3D::Draw(const DirectX::SimpleMath::Matrix& view)
{
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

	// モデルの描画
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}
