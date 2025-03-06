/**
 * @file   ComponentsBace.h
 *
 * @brief  レンダラーコンポート基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#include "pch.h"
#include "RendererBace.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="tag">Component Name</param>
/// <param name="pStates">Common States</param>
RendererBace::RendererBace(std::string name, DirectX::CommonStates* pStates)
	: ComponentsBace(Tags::Render, name)
	, mp_States{ pStates }
{
}

RendererBace::~RendererBace()
{
	mp_States = nullptr;
}
