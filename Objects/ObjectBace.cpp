#include "pch.h"
#include "ObjectBace.h"

#include "../Scenes/SceneBace.h"
#include "Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_Scene{ pScene }
{
	m_Transform = std::make_unique<Transform>();
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_Scene = nullptr;
	m_Transform.reset();
}
