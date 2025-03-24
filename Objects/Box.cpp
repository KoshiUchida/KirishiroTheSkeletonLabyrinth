/**
 * @file   Box.cpp
 *
 * @brief  �{�b�N�X�I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "Box.h"

#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

using namespace DirectX;

Box::Box(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform>());

	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);

	AddComponent(std::make_unique<BoxCollider>(mp_Scene, "Collider", pTransform, SimpleMath::Vector3(2.f, 2.f, 2.f)));
}

Box::~Box() noexcept = default;

void Box::Initialize()
{
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));
	pTransform->SetScale(0.35f);
}

void Box::Process(float elapsedTime)
{
	// �x�����
	elapsedTime;

	// Player�̃|�C���^���擾
	ObjectBace* player = GetObjectPtr("Player");

	// �擾���s���̑������^�[��
	if (!player)
		return;

	// Player�������o��
	static_cast<ColliderBace*>(player->GetComponentPtr("Collider"))
		->Collision(
			static_cast<ColliderBace*>(GetComponentPtr("Collider"))
		);
}
