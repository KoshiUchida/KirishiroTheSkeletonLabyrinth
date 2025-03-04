#include "pch.h"
#include "ObjectBace.h"

#include "../Scenes/SceneBace.h"
#include "Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_Scene{ pScene }
{
	m_Transform = std::make_unique<Transform>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_Scene = nullptr;
	m_Transform.reset();
}
