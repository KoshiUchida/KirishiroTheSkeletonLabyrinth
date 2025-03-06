/**
 * @file   ComponentsBace.cpp
 *
 * @brief  コンポート基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#include "pch.h"
#include "ComponentsBace.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="tag">種類</param>
/// <param name="name">名称</param>
ComponentsBace::ComponentsBace(Tags tag, const std::string& name) noexcept
	: m_Tag{ tag }
	, m_Name{ name }
{
}

/// <summary>
/// Destructor
/// </summary>
ComponentsBace::~ComponentsBace() noexcept = default;
