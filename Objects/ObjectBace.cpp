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
#include "../Components/ComponentsBace.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() }
	, mp_Scene        { pScene }
{
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_ObjectManager = nullptr;
	mp_Scene = nullptr;


	for (auto& element : m_Components)
		element.second.reset();

	m_Components.clear();
}

/// <summary>
/// コンポーネントの追加
/// </summary>
/// <param name="component">追加するコンポーネント</param>
void ObjectBace::AddComponent(std::unique_ptr<ComponentsBace> component)
{
	std::string AddName{ component->GetName() };

	m_Components.emplace(AddName, std::move(component));
}

/// <summary>
/// コンポーネントへのポインタの取得
/// </summary>
/// <returns>コンポーネントへのポインタまたはNULL</returns>
ComponentsBace* ObjectBace::GetComponentPtr(const std::string& tag)
{
	if (m_Components.count(tag) == 0)
	{
		return nullptr;
	}

	return m_Components.at(tag).get();
}

std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>* ObjectBace::GetComponentsPtr()
{
	return &m_Components;
}

