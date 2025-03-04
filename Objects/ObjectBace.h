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
#include <memory>

class SceneBace;
class Transform;

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class ObjectBace
{
protected:
	// シーンへのポインタ
	SceneBace* mp_Scene;

	// トランスフォーム
	std::unique_ptr<Transform> m_Transform;

public:
	// Constructor & Destructor
	ObjectBace(SceneBace* pScene) noexcept;
	virtual ~ObjectBace() noexcept;

	// Main System
	virtual void Initialize(                 ) = 0;
	virtual void Update    (float elapsedTime) = 0;
};

