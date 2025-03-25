/**
 * @file   Goal.cpp
 *
 * @brief  �S�[���I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 */

#include "pch.h"
#include "Goal.h"

// �g�p����R���|�l�[�g
#include "../Components/Transform.h"
#include "../Components/Renderer3D.h"
#include "../Components/BoxCollider.h"

// �֘A����N���X
#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"

// �֘A����I�u�W�F�N�g
#include "Player.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
Goal::Goal(SceneBace* pScene, const std::string& name, const DirectX::SimpleMath::Vector3& position) noexcept
	: ObjectBace(pScene, name)
{
	// �g�����X�t�H�[���̒ǉ�
	AddComponent(make_unique<Transform>());

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ���W�̐ݒ�
	pTransform->SetPosition(position);

	// �����_���[3D�̒ǉ�
	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Goal.sdkmesh"));

	// �{�b�N�X�R���C�_�[�̒ǉ�
	AddComponent(make_unique<BoxCollider>(pScene, "Collider", pTransform, SimpleMath::Vector3(1.f, 1.f, 1.f)));
}

/// <summary>
/// Destructor
/// </summary>
Goal::~Goal() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void Goal::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Goal::Process(float elapsedTime)
{
	// �x�����p
	elapsedTime;

	// �v���C���[�̎擾
	ObjectBace* pPlayer = mp_ObjectManager->GetObjectPtr("Player");
	
	// �v���C���[���擾�ł��Ȃ������ۂ̑������^�[��
	if (!pPlayer)
		return;

	// �v���C���[�R���C�_�[�̎擾
	BoxCollider* playerCollider = static_cast<BoxCollider*>(pPlayer->GetComponentPtr("Collider"));

	// �����A�v���C���[�Əd�Ȃ����烊�U���g�V�[���ɑJ�ڂ���
	if (playerCollider->IsHit(static_cast<BoxCollider*>(GetComponentPtr("Collider"))))
	{
		mp_Scene->ChangeScene("Result");
	}
}
