/**
 * @file   SceneBace.h
 *
 * @brief  シーンの基底クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#pragma once

#include <string>
#include "DeviceResources.h"

class SceneManager;
class ObjectBace;

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

	/*取得*/
	DX::DeviceResources* GetDeviceResourcesPointer() { return mp_DeviceResources; }
	DirectX::SimpleMath::Matrix* GetProjPointer()    { return mp_Proj; }
	DirectX::CommonStates* GetCommonStatesPointer()  { return mp_States; }
	SceneManager* GetSceneManagerPtr();

public:
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

protected:
	// オブジェクトの追加
	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object) noexcept(false);

	// オブジェクトへのポインタの取得
	ObjectBace* GetObjectPtr(const std::string& objectName);
};

