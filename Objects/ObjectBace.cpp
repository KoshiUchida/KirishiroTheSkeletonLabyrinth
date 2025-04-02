/**
 * @file   ObjectBace.cpp
 *
 * @brief  オブジェクト基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"
#include "../Managers/SceneManager.h" 
#include "../Components/ComponentsBace.h"
#include "../Components/RendererBace.h"
#include "../Components/SphereCollider.h"
#include "../Components/Renderer3DWithAnimation.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene, const std::string& name) noexcept :
	mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() },
	mp_Scene        { pScene },
	m_Name          { name },
	m_Layer         { 0 }
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
		else if (component.second->GetTag() == ComponentsBace::Tags::UAndR)
		{
			static_cast<Renderer3DWithAnimation*>(component.second.get())->Update(elapsedTime);
		}
		else
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
			SphereCollider* sphere = static_cast<SphereCollider*>(component.second.get());
			if (sphere)
				sphere->Render(view);
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::UAndR)
		{
			static_cast<Renderer3DWithAnimation*>(component.second.get())->Draw(view);
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
/// レイヤーの設定関数
/// </summary>
void ObjectBace::SetLayer(int layer)
{
	m_Layer = layer;
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

/// <summary>
/// 名前の取得関数
/// </summary>
/// <returns>このオブジェクトの名前</returns>
std::string ObjectBace::GetName() const noexcept
{
	return m_Name;
}

/// <summary>
/// レイヤーの取得関数
/// </summary>
int ObjectBace::GetLayer() const noexcept
{
	return m_Layer;
}

