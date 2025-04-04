/**
 * @file   ObjectManager.h
 *
 * @brief  オブジェクト管理クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/01
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "../Objects/ObjectBace.h"

class ComponentsBace;
class RendererBace;

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

	// 削除予定のオブジェクト名前
	std::vector<std::string> m_DeleteObjectNames;

	// 最大のレイヤー
	int m_MaxLayer;

	// 最小のレイヤー
	int m_MinLayer;

public:
	// Main System
	ObjectManager() noexcept;
	~ObjectManager() noexcept;
	void Update(float elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& view);
	void Finalize();

	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	ObjectBace* GetObjectPtr(const std::string& objectName);

	void DeleteObject(ObjectBace* pObject);

	std::vector<std::string> FindObjects(const std::string& findName);
};

