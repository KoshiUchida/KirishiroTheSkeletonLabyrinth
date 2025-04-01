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

// �֌W����Ǘ��N���X
#include "../Managers/ObjectManager.h"

// �֌W����I�u�W�F�N�g
#include "CircleButtonEffect.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
OparateUI::OparateUI(SceneBace* pScene, const std::string& name) noexcept :
	ObjectBace(pScene, name),
	m_EffectCount{ 0 },
	m_Key{}
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

	pTransform->SetPosition(SimpleMath::Vector2(-140.f, -130.f));

	pTransform->SetOrigin(Transform2D::ScreenOrigin::DownRight);
}

/// <summary>
/// �X�V����
/// </summary>
void OparateUI::Process(float elapsedTime)
{
	// �x�����
	elapsedTime;

	// �G�t�F�N�g�Ƃ̍��W�̈Ⴂ
	static constexpr float EffectOffset{ 70.f };

	// �G�t�F�N�g�̕\������[s]
	static constexpr float EffectLimit{ 0.9f };

	// �G�t�F�N�g�̑傫��
	static constexpr float EffectScale{ 0.4f };

	// �L�[�{�[�h�̏�Ԏ擾
	Keyboard::State kb = Keyboard::Get().GetState();

	// �g�����X�t�H�[���̎擾
	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	// �����_���[�̎擾
	Renderer2D* pRnderer = static_cast<Renderer2D*>(GetComponentPtr("MainUI"));

	// �G�t�F�N�g�J�E���g��100���z���Ă����烊�Z�b�g
	if (m_EffectCount > 100)
		m_EffectCount = 0;

	// �����A�L�[��Ԃ�TURE�ɂȂ��Ă����猻�݂̏�Ԃ����
	if (m_Key.up)
		m_Key.up    = kb.C || kb.I;
	if (m_Key.down)
		m_Key.down  = kb.X || kb.K;
	if (m_Key.left)
		m_Key.left  = kb.Z || kb.J;
	if (m_Key.right)
		m_Key.right = kb.V || kb.L;

	// �L�[�ɉ������G�t�F�N�g�̐���
	// ��L�[��������Ă��邩  
	if (m_Key.up == false && (kb.C || kb.I))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene,
				GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(0.f, -EffectOffset),
				EffectScale,
				EffectLimit
				)
		);

		m_Key.up = true;
	}
	// ���L�[��������Ă��邩
	if (m_Key.down == false && (kb.X || kb.K))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(0.f, EffectOffset),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.down = true;
	}
	// ���L�[��������Ă��邩
	if (m_Key.left == false && (kb.Z || kb.J))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(-EffectOffset, 0.f),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.left = true;
	}
	// �E�L�[��������Ă��邩
	if (m_Key.right == false && (kb.V || kb.L))
	{
		mp_ObjectManager->AddObject(
			GetName() + std::to_string(m_EffectCount),
			std::make_unique<CircleButtonEffect>(
				mp_Scene, GetName() + std::to_string(m_EffectCount++),
				pTransform->GetPosition(pRnderer->GetDeviceResources()) + SimpleMath::Vector2(EffectOffset, 0.f),
				EffectScale,
				EffectLimit
			)
		);

		m_Key.right = true;
	}
}
