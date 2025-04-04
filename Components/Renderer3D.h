/**
 * @file   Renderer3D.h
 *
 * @brief  モデル描画コンポーネントのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#pragma once
#include "RendererBace.h"
#include <memory>
#include "DeviceResources.h"

class Transform;
class SceneBace;

/// <summary>
/// 3Dモデル描画クラス
/// </summary>
class Renderer3D
	: public RendererBace
{
public:
	// モデルの読み込み形式
	enum class Read
	{
		SDK,
		CMO
	};

private:
	// トランスフォームへのポインタ
	Transform* mp_Transform;

	// モデル
	std::unique_ptr<DirectX::Model> m_Model;

	// デバイスリソースへのポインタ
	DX::DeviceResources* mp_DeviceResources;

	// 射影行列
	DirectX::SimpleMath::Matrix* mp_Proj;

public:
	Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath, Read read = Read::SDK) noexcept(false);
	~Renderer3D() noexcept;
	void Draw(const DirectX::SimpleMath::Matrix& view) override final;
};

