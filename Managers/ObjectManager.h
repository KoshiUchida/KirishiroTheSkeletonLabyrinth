/**
 * @file   ObjectManager.h
 *
 * @brief  オブジェクト管理クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "../Objects/ObjectBace.h"

/// <summary>
/// オブジェクト管理クラス
/// </summary>
class ObjectManager
{
private:
	// エイリアス宣言
	using ObjectCollection
		= std::unordered_map<std::string, std::unique_ptr<ObjectBace>>;

	// オブジェクトの集合
	ObjectCollection m_Objects;

public:
	// Main System
	ObjectManager() noexcept;
	~ObjectManager() noexcept;
	void Update(float elapsedTime);
	void Finalize();

	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	ObjectBace* GetObjectPtr(const std::string& objectName);
};

