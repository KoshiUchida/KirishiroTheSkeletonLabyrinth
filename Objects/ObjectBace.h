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

	// オブジェクトの名前
	std::string m_Name;

	// レイヤー
	int m_Layer;

public:
	// Constructor & Destructor
	ObjectBace(SceneBace* pScene, const std::string& name) noexcept;
	virtual ~ObjectBace() noexcept;

	// Main System
	virtual void Initialize(                 ) = 0;
	virtual void Process   (float elapsedTime) = 0;
	void Update(float elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& view);

	void AddComponent(std::unique_ptr<ComponentsBace> component);

	void SetLayer(int layer);

	ComponentsBace* GetComponentPtr(const std::string& name);
	ObjectBace* GetObjectPtr(const std::string& name);
	std::string GetName() const noexcept;
	int GetLayer() const noexcept;
};

