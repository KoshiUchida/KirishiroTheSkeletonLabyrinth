/**
 * @file   CircleButtonEffect.cpp
 *
 * @brief  �~�^�{�^���̃G�t�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "CircleButtonEffect.h"

// �֌W�̂���w�b�_�[
#include "../Managers/ObjectManager.h"
#include "../Common/Easing.h"

// �g�p����R���|�[�l���g
#include "../Components/Transform2D.h"
#include "../Components/Renderer2D.h"

/// <summary>
/// Constructor
/// </summary>
CircleButtonEffect::CircleButtonEffect(SceneBace* pScene, const std::string& name, DirectX::SimpleMath::Vector2 position, float size, float limit) noexcept :
	ObjectBace(pScene, name),
	m_Limit{ limit },
	m_Now{ 0.f }
{
	SetLayer(2);

	AddComponent(std::make_unique<Transform2D>());

	Transform2D* pTransform = static_cast<Transform2D*>(GetComponentPtr("Transform"));

	pTransform->SetPosition(position);
	pTransform->SetScale(size);

	AddComponent(std::make_unique<Renderer2D>(mp_Scene, "Circle", pTransform, L"Resources\\Textures\\CircleEffect.dds"));
}

/// <summary>
/// Destructor
/// </summary>
CircleButtonEffect::~CircleButtonEffect() noexcept = default;

/// <summary>
///  ����������
/// </summary>
void CircleButtonEffect::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void CircleButtonEffect::Process(float elapsedTime)
{
	// ���Ԃ̌o�߂�ۑ�
	m_Now += elapsedTime;

	// ���Ԃ̌o�߂�������z�����玩��
	if (m_Now > m_Limit)
	{
		mp_ObjectManager->DeleteObject(this);
		return;
	}

	// ���Ԃ̌o�߂��p�[�Z���g�ɕϊ�
	float parcent = m_Now / m_Limit;

	// 2���������_���[�̎擾
	Renderer2D* pRenderer = static_cast<Renderer2D*>(GetComponentPtr("Circle"));

	// �����x�̑���
	if (parcent <= 0.3f)
	{
		parcent /= 0.3f;
		pRenderer->SetAlpha(EaseOutQuint(parcent));
	}
	else
	{
		parcent = 0.7f - (parcent - 0.3f);
		pRenderer->SetAlpha(EaseInOutSine(parcent));
	}
}
