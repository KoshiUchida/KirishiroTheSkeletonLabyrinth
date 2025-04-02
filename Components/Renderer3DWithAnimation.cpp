/**
 * @file   Renderer3DWithAnimation.cpp
 *
 * @brief  アニメーション付き3次元レンダラーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "Renderer3DWithAnimation.h"

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
Renderer3DWithAnimation::Renderer3DWithAnimation(
	SceneBace* pScene,
	std::string name,
	Transform* pTransform,
	const wchar_t* modelPath) noexcept :
	ComponentsBace(ComponentsBace::Tags::UAndR, name),
	mp_States         { pScene->GetCommonStatesPointer()},
	mp_DeviceResources{ pScene->GetDeviceResourcesPointer() },
	mp_Proj           { pScene->GetProjPointer() },
	mp_Transform      { pTransform }
{
	// デバイスの取得
	auto device = mp_DeviceResources->GetD3DDevice();

	// エフェクトファクトリーの作成
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Textures");

	// モデルの読み込み
	m_Model = Model::CreateFromSDKMESH(device, modelPath,
		fx,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);

	m_drawBones = ModelBone::MakeArray(m_Model->bones.size());

	m_Model->UpdateEffects([&](IEffect* effect)
		{
			auto skin = dynamic_cast<SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		}
	);
}

/// <summary>
/// Destructor
/// </summary>
Renderer3DWithAnimation::~Renderer3DWithAnimation() noexcept
{
	m_Animation.Release();

	m_Model.reset();
}

/// <summary>
/// 再生するアニメーションの設定関数
/// </summary>
void Renderer3DWithAnimation::SetAnimation(const wchar_t* animationPath)
{
	DX::ThrowIfFailed(
		m_Animation.Load(animationPath)
	);

	m_Animation.Bind(*m_Model);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapseTime">経過時間[s]</param>
void Renderer3DWithAnimation::Update(float elapseTime)
{
	// アニメーションの更新処理
	m_Animation.Update(elapseTime);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー行列</param>
void Renderer3DWithAnimation::Draw(const DirectX::SimpleMath::Matrix& view)
{
	// コンテキストの取得
	auto context = mp_DeviceResources->GetD3DDeviceContext();
	size_t nbones = m_Model->bones.size();

	// アニメーションの適用
	m_Animation.Apply(*m_Model, nbones, m_drawBones.get());

	// ワールド行列
	SimpleMath::Matrix world;

	// 平行移動する行列を作成する
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X軸で回転する行列を作成する
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y軸で回転する行列を作成する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z軸で回転する行列を作成する
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationZ(mp_Transform->GetRotateZ());

	// 拡大する行列を作成する
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ワールド行列へ統合
	world = scale * rotZ * rotY * rotX * trans;

	// モデルの描画
	m_Model->DrawSkinned(context, *mp_States, nbones, m_drawBones.get(),
		world, view, *mp_Proj);
}
