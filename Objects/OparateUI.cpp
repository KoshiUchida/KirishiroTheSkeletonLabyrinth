/**
 * @file   OparateUI.cpp
 *
 * @brief  �I�y���[�^UI�I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "OparateUI.h"

 // �g�p����R���|�[�l���g
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

/// <summary>
/// Constructor
/// </summary>
OparateUI::OparateUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name)
{
	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "MainUI", pTransform, L"Resources\\Textures\\OparationUI.dds"));
}

/// <summary>
/// Destructor
/// </summary>
OparateUI::~OparateUI() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void OparateUI::Initialize()
{
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(DirectX::SimpleMath::Vector2(-140.f, -130.f));

	pTransform->SetOrigin(Transform2D::ScreenOrigin::DownRight);
}

/// <summary>
/// �X�V����
/// </summary>
void OparateUI::Process(float elapsedTime)
{
}
