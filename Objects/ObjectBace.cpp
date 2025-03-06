/**
 * @file   ObjectBace.cpp
 *
 * @brief  オブジェクト基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"
#include "../Managers/SceneManager.h" 

/// <summary>
/// コンストラクタ
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() }
	, mp_Scene        { pScene }
{
	m_Transform = std::make_unique<Transform>();
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_ObjectManager = nullptr;
	mp_Scene = nullptr;
	m_Transform.reset();
}

