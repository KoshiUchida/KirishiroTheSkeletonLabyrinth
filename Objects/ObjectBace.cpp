/**
 * @file   ObjectBace.cpp
 *
 * @brief  オブジェクト基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Scenes/SceneBace.h"

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
