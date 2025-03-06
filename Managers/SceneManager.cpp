/**
 * @file   SceneManaager.cpp
 *
 * @brief  シーンの管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "SceneManager.h"

// コンストラクタ
SceneManager::SceneManager()
	: m_pCurrentScene  { nullptr }
	, m_pRequestedScene{ nullptr }
	, m_scenes         {}
	, m_IsEnd          {}
{
	m_ObjectManager = std::make_unique<ObjectManager>();
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();

	m_ObjectManager.reset();
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update(const float elapsedTime)
{
	// シーンの変更要求があった場合はシーンの変更を行う
	if (m_pRequestedScene)
	{
		ChangeScene();
	}

	// 現在のシーンを更新
	if (m_pCurrentScene)
		m_pCurrentScene->Update(elapsedTime);

	// オブジェクトの更新
	m_ObjectManager->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Render()
{
	// 現在のシーンを描画
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

/// <summary>
/// シーンの登録
/// </summary>
/// <param name="sceneName">シーンの登録名</param>
/// <param name="scene">登録シーン</param>
void SceneManager::addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/// <summary>
/// 開始シーンの設定
/// </summary>
/// <param name="startSceneName">開始シーン名</param>
void SceneManager::SetStartScene(const std::string& startSceneName)
{
	RequestSceneChange(startSceneName);
}

/// <summary>
/// シーン変更の要求
/// </summary>
/// <param name="changeSceneName">変更予定のシーン名</param>
void SceneManager::RequestSceneChange(const std::string& changeSceneName)
{
	if (changeSceneName == "End")
	{
		m_IsEnd = true;
		return;
	}

	if (m_scenes.count(changeSceneName) == 0)
	{
		// Error
		return;
	}

	m_pRequestedScene = m_scenes[changeSceneName].get();
}

/// <summary>
/// オブジェクトの追加
/// </summary>
/// <param name="objectName">追加するオブジェクト名</param>
/// <param name="object">追加するオブジェクト</param>
void SceneManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	m_ObjectManager->AddObject(objectName, std::move(object));
}

/// <summary>
/// オブジェクトのポインタ取得
/// </summary>
/// <param name="objectName">オブジェクトの名前</param>
/// <returns></returns>
ObjectBace* SceneManager::GetObjectPtr(const std::string& objectName)
{
	return m_ObjectManager->GetObjectPtr(objectName);
}

/// <summary>
/// 共有データの取得
/// </summary>
/// <param name="key">取得したい共有データのキー</param>
/// <returns>キーの共有データ</returns>
std::string SceneManager::GetShareData(const std::string& key) const
{
	if (m_shareData.count(key) == 0)
	{
		// Error
		return std::string{};
	}

	return m_shareData.at(key);
}

ObjectManager* SceneManager::GetObjectManagerPtr()
{
	return m_ObjectManager.get();
}

/// <summary>
/// 共有データの設定
/// </summary>
/// <param name="key">設定したい共有データのキー</param>
/// <param name="value">設定したい共有データの値</param>
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_shareData[key] = value;
}

/// <summary>
/// シーンの変更
/// </summary>
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
		return;

	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();
	
	m_ObjectManager->Finalize();

	if (m_IsEnd)
		return;

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();

	m_pRequestedScene = nullptr;
}
