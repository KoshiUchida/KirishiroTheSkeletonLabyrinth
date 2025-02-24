/**
 * @file   SceneBace.cpp
 *
 * @brief  シーンの基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/12
 */

#include "pch.h"
#include "SceneBace.h"

#include "../Managers/SceneManager.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="pSceneManager">シーンマネージャへのポインタ</param>
SceneBace::SceneBace
(
	               SceneManager* pSceneManager,
	        DX::DeviceResources* pDeviceResources,
	DirectX::SimpleMath::Matrix* pProj,
	      DirectX::CommonStates* pStates
) noexcept(false)
	: mp_SceneManager    { pSceneManager }
	, mp_DeviceResources { pDeviceResources }
	, mp_Proj            { pProj }
	, mp_States          { pStates }
{
}

/// <summary>
/// Destructor
/// </summary>
SceneBace::~SceneBace() noexcept = default;

/// <summary>
/// シーンの変更
/// </summary>
/// <param name="nextSceneName">変更先のシーン名</param>
void SceneBace::ChangeScene(const std::string& nextSceneName) noexcept(false)
{
	mp_SceneManager->RequestSceneChange(nextSceneName);
}

/// <summary>
/// 共有データの読み込み
/// </summary>
/// <param name="key">共有データキー</param>
/// <param name="pValue">読み込み先</param>
void SceneBace::ReadSharedData(const std::string& key, int* pValue) const noexcept(false)
{
	*pValue = std::stoi(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, float* pValue) const noexcept(false)
{
	*pValue = std::stof(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, std::string* pValue) const noexcept(false)
{
	*pValue = mp_SceneManager->GetShareData(key);
}

/// <summary>
/// 共有データへの書き込み
/// </summary>
void SceneBace::WriteSharedData(const std::string& key, int value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, float value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, std::string value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, value);
}

