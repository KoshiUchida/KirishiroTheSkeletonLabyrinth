#include "pch.h"
#include "Box.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/SphereCollider.h"

using namespace DirectX;

Box::Box(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	AddComponent(std::make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Kirishiro.sdkmesh"));

	AddComponent(std::make_unique<SphereCollider>("Collider", pTransform, 1.f, mp_Scene));
}

Box::~Box() noexcept = default;

void Box::Initialize()
{
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetPositionX(2.f);
	pTransform->SetScale(0.35f);
}

void Box::Process(float elapsedTime)
{
}
