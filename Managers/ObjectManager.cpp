/**
 * @file   ObjectManager.cpp
 *
 * @brief  オブジェクト管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#include "pch.h"
#include "ObjectManager.h"
#include "../Components/ComponentsBace.h"
#include "../Components/RendererBace.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectManager::ObjectManager() noexcept :
	m_MaxLayer{ 0 },
	m_MinLayer{ 0 }
{
}

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

	// 削除予定のオブジェクトの削除
	for (int i{ 0 }; i < m_DeleteObjectNames.size(); i++)
	{
		m_Objects.erase(m_DeleteObjectNames[i]);
		m_DeleteObjectNames.erase(m_DeleteObjectNames.begin() + i);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ObjectManager::Render(const DirectX::SimpleMath::Matrix& view)
{
	// オブジェクトの描画処理
	for (int i{ m_MinLayer }; i <= m_MaxLayer; i++)
		for (auto& element : m_Objects)
			if (element.second->GetLayer() == i)
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

	m_MaxLayer = 0;
	m_MinLayer = 0;
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

	// レイヤーの最小と最大を確認
	if (object->GetLayer() > m_MaxLayer)
		m_MaxLayer = object->GetLayer();
	if (object->GetLayer() < m_MinLayer)
		m_MinLayer = object->GetLayer();

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

/// <summary>
/// 対象オブジェクトの削除
/// </summary>
/// <param name="pObject">削除するオブジェクト</param>
void ObjectManager::DeleteObject(ObjectBace* pObject)
{
	// オブジェクトが存在しない場合は処理を行わない
	if (m_Objects.count(pObject->GetName()) == 0)
		return;

	// オブジェクトの名前を保存
	m_DeleteObjectNames.push_back(pObject->GetName());
}

/// <summary>
/// 一致する文字列群の取得関数
/// </summary>
std::vector<std::string> ObjectManager::FindObjects(const std::string& findName)
{
	std::vector<std::string> FoundNames;

	for (auto& element : m_Objects)
		if (element.second->GetName().find(findName) != std::string::npos)
			FoundNames.push_back(element.second->GetName());

	return FoundNames;
}
