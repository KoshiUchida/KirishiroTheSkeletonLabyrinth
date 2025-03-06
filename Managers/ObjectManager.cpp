/**
 * @file   ObjectManager.cpp
 *
 * @brief  オブジェクト管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "ObjectManager.h"
#include "../Components/ComponentsBace.h"
#include "../Components/RendererBace.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectManager::ObjectManager() noexcept = default;

/// <summary>
/// デストラクタ
/// </summary>
ObjectManager::~ObjectManager() noexcept
{
	Finalize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ObjectManager::Update(float elapsedTime)
{
	// 更新処理のあるコンポーネントの処理
	// TODO::タグ「Update」のコンポーネントを作成したら修正する
	for (auto& component : m_UpdateComponent);

	// オブジェクトの更新処理
	for (auto& element : m_Objects)
		element.second->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
void ObjectManager::Render(const DirectX::SimpleMath::Matrix& view)
{
	// 描画処理のあるコンポーネントの処理
	for (auto& component : m_RenderComponent)
		component->Draw(view);
}

/// <summary>
/// 終了処理
/// </summary>
void ObjectManager::Finalize()
{
	for (auto& element : m_Objects)
		element.second.reset();

	m_Objects.clear();
}

/// <summary>
/// オブジェクトの追加
/// </summary>
/// <param name="objectName">追加するオブジェクト名</param>
/// <param name="object">追加するオブジェクトデータ</param>
void ObjectManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	// 新規オブジェクトの初期化処理
	object->Initialize();

	// オブジェクトのコンポーネント群へのポインタの取得
	std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>*
		NewObjectComponents = object->GetComponentsPtr();

	// コンポーネントの登録
	for (auto& component : (*NewObjectComponents))
	{
		if (component.second->GetTag() == ComponentsBace::Tags::Update)
		{
			// TODO::タグ「Update」のコンポーネントを作成したら修正する
			m_UpdateComponent.push_back(component.second.get());
		}
		else if (component.second->GetTag() == ComponentsBace::Tags::Render)
		{
			m_RenderComponent.push_back(static_cast<RendererBace*>(component.second.get()));
		}
	}

	// オブジェクトの登録
	m_Objects.emplace(objectName, std::move(object));
}

ObjectBace* ObjectManager::GetObjectPtr(const std::string& objectName)
{
	if (m_Objects.count(objectName) == 0)
	{
		return nullptr;
	}

	return m_Objects.at(objectName).get();
}
