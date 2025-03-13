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
	// オブジェクトの更新処理
	for (auto& element : m_Objects)
		element.second->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
void ObjectManager::Render(const DirectX::SimpleMath::Matrix& view)
{
	// オブジェクトの描画処理
	for (auto& element : m_Objects)
		element.second->Render(view);
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
