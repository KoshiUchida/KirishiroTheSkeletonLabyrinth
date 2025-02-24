/**
 * @file   SceneBace.h
 *
 * @brief  シーンの基底クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#pragma once

#include <string>
#include "DeviceResources.h"

class SceneManager;

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBace
{
protected:
	// シーンマネージャへのポインタ
	SceneManager* mp_SceneManager;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

	// 共通ステート
	DirectX::CommonStates* mp_States;

public:
	/*メインシステム*/
	        SceneBace
			(
				SceneManager* pSceneManager,
				DX::DeviceResources* pDeviceResources,
				DirectX::SimpleMath::Matrix* pProj,
				DirectX::CommonStates* pStates
			) noexcept(false);
	virtual ~SceneBace () noexcept;
	virtual void Initialize (                       ) = 0;
	virtual void Update     (const float elapsedTime) = 0;
	virtual void Render     (                       ) = 0;
	virtual void Finalize   (                       ) = 0;

protected:
	/*内部実装*/
	// シーンの変更
	void ChangeScene(const std::string& nextSceneName) noexcept(false);

	// 共有データの読み込み
	void ReadSharedData (const std::string& key, int*         pValue) const noexcept(false);
	void ReadSharedData (const std::string& key, float*       pValue) const noexcept(false);
	void ReadSharedData (const std::string& key, std::string* pValue) const noexcept(false);

	// 共有データへの書き込み
	void WriteSharedData (const std::string& key, int         value) noexcept(false);
	void WriteSharedData (const std::string& key, float       value) noexcept(false);
	void WriteSharedData (const std::string& key, std::string value) noexcept(false);
};

