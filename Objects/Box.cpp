/**
 * @file   Box.cpp
 *
 * @brief  ボックスオブジェクトのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "Box.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

using namespace DirectX;

Box::Box(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(1.f, 1.f, 1.f)));
}

Box::~Box() noexcept = default;

void Box::Initialize()
{
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetScale(0.35f);
}

void Box::Process(float elapsedTime)
{
	// 警告回避分
	elapsedTime;
}
