/**
 * @file   SceneManaager.h
 *
 * @brief  シーンの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2024/11/03
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class SceneBace;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
private:
	// エイリアス宣言
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<SceneBace>>;
	using ShareData       = std::unordered_map<std::string, std::string>;

	// シーンの集合体
	SceneCollection m_scenes;

	// 現在のシーン
	SceneBace* m_pCurrentScene;
	// 変更要求のあったシーン
	SceneBace* m_pRequestedScene;

	// 共有データ
	ShareData m_shareData;

	// 終了命令
	bool m_IsEnd;

public:
	/*メインシステム*/
	SceneManager  ();
	~SceneManager ();
	void Update (const float elapsedTime);
	void Render ();

	// シーンの登録
	void addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene);

	// 起動時のシーンの設定
	void SetStartScene(const std::string& startSceneName);

	// シーン変更の要求
	void RequestSceneChange(const std::string& changeSceneName);

	/*取得/設定*/
	// 共有データの取得
	std::string GetShareData(const std::string& key) const;

	// 終了命令の取得
	bool isEnd() const { return m_IsEnd; }

	// 共有データの設定
	void SetSharedData(const std::string& key, const std::string& value);

private:
	// シーンの変更
	void ChangeScene();

};

