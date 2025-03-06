/**
 * @file   ObjectBace.h
 *
 * @brief  オブジェクト基底クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class ObjectManager;
class SceneBace;
class ComponentsBace;

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class ObjectBace
{
protected:
	// エイリアス宣言
	using ComponentsCollection = std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>;

	// オブジェクトマネージャへのポインタ
	ObjectManager* mp_ObjectManager;

	// シーンへのポインタ
	SceneBace* mp_Scene;

	// コンポネートの集合
	ComponentsCollection m_Components;

public:
	// Constructor & Destructor
	ObjectBace(SceneBace* pScene) noexcept;
	virtual ~ObjectBace() noexcept;

	// Main System
	virtual void Initialize(                 ) = 0;
	virtual void Update    (float elapsedTime) = 0;

	void AddComponent(std::unique_ptr<ComponentsBace> component);

	ComponentsBace* GetComponentPtr(const std::string& tag);
	std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>* GetComponentsPtr();
};

