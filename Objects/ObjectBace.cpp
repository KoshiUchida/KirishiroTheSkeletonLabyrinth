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
#include "../Components/RendererBace.h"
#include "../Components/SphereCollider.h"

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
/// オブジェクト全体の更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ObjectBace::Update(float elapsedTime)
{
	Process(elapsedTime);

	for (auto& component : m_Components)
	{
		if (component.second->GetTag() == ComponentsBace::Tags::Update)
		{
			// TODO::タグ「Update」のコンポーネントを作成したら修正する
		}
		component;
	}
}

/// <summary>
/// オブジェクト全体の描画処理
/// </summary>
void ObjectBace::Render(const DirectX::SimpleMath::Matrix& view)
{
	for (auto& component : m_Components)
	{
		if (component.second->GetTag() == ComponentsBace::Tags::Render)
		{
			static_cast<RendererBace*>(component.second.get())->Draw(view);
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::Collider)
		{
			static_cast<SphereCollider*>(component.second.get())->Render(view);
		}
		else
			component;
	}
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
ComponentsBace* ObjectBace::GetComponentPtr(const std::string& name)
{
	if (m_Components.count(name) == 0)
	{
		return nullptr;
	}

	return m_Components.at(name).get();
}

ObjectBace* ObjectBace::GetObjectPtr(const std::string& name)
{
	return mp_ObjectManager->GetObjectPtr(name);
}

