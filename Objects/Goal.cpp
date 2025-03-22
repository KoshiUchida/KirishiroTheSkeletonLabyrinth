/**
 * @file   Goal.cpp
 *
 * @brief  �S�[���I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/22
 */

#include "pch.h"
#include "Goal.h"

// �g�p����R���|�l�[�g
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

	// �g�����X�t�H�[���̎擾
	Transform* pTransform = static_cast<Transform*>(GetComponentPtr("Transform"));

	// ���W�̐ݒ�
	pTransform->SetPosition(position);

	AddComponent(make_unique<Renderer3D>(pScene, pTransform, L"Resources\\Models\\Goal.sdkmesh"));
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
}
