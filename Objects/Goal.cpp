/**
 * @file   Goal.cpp
 *
 * @brief  ゴールオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/22
 */

#include "pch.h"
#include "Goal.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
Goal::Goal(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene)
{
	AddComponent(make_unique<Transform>());

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 座標の設定
	pTransform->SetPosition(position);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Goal.sdkmesh"));
}

/// <summary>
/// Destructor
/// </summary>
Goal::~Goal() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Goal::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Goal::Process(float elapsedTime)
{
	// 警告回避用
	elapsedTime;
}
