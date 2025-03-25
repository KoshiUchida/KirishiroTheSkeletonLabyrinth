/**
 * @file   Goal.cpp
 *
 * @brief  ゴールオブジェクトのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "Goal.h"

// 使用するコンポネート
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

// 関連するクラス
#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"

// 関連するオブジェクト
#include "Player.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
Goal::Goal(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
{
	// トランスフォームの追加
	AddComponent(make_unique<Transform>());

	// トランスフォームの取得
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// 座標の設定
	pTransform->SetPosition(position);

	// レンダラー3Dの追加
	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Goal.sdkmesh"));

	// ボックスコライダーの追加
	AddComponent(make_unique<BoxCollider>(pScene, "Collider", pTransform, SimpleMath::Vector3(1.f, 1.f, 1.f)));
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

	// プレイヤーの取得
	ObjectBace* pPlayer = mp_ObjectManager->GetObjectPtr("Player");
	
	// プレイヤーを取得できなかった際の早期リターン
	if (!pPlayer)
		return;

	// プレイヤーコライダーの取得
	BoxCollider* playerCollider = static_cast<BoxCollider*>(pPlayer->GetComponentPtr("Collider"));

	// もし、プレイヤーと重なったらリザルトシーンに遷移する
	if (playerCollider->IsHit(static_cast<BoxCollider*>(GetComponentPtr("Collider"))))
	{
		mp_Scene->ChangeScene("Result");
	}
}
