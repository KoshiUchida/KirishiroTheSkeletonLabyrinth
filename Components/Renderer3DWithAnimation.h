/**
 * @file   Renderer3DWithAnimation.h
 *
 * @brief  アニメーション付き3次元レンダラーのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#pragma once
#include "ComponentsBace.h"

#include <memory>
#include <unordered_map>
#include "DeviceResources.h"
#include "Animation.h"

class Transform;
class SceneBace;

/// <summary>
/// アニメーション付き3次元レンダラーコンポネートクラス
/// </summary>
class Renderer3DWithAnimation :
    public ComponentsBace
{
private:
    // 共通ステート
    DirectX::CommonStates* mp_States;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// トランスフォームへのポインタ
	Transform* mp_Transform;

	// モデル
	std::unique_ptr<DirectX::Model> m_Model;

	// モデルのボーン
	DirectX::ModelBone::TransformArray m_drawBones;

	// アニメーション群
	DX::AnimationSDKMESH m_Animation;

public:
    /*Main System*/
    Renderer3DWithAnimation(SceneBace* pScene, std::string name, Transform* pTransform, const wchar_t* modelPath) noexcept;
    ~Renderer3DWithAnimation() noexcept;

	void SetAnimation(const wchar_t* animationPath);

	void Update(float elapseTime);
	void Draw(const DirectX::SimpleMath::Matrix& view);
};

