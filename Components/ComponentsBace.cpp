/**
 * @file   ComponentsBace.cpp
 *
 * @brief  �R���|�[�g���N���X�̃\�[�X�t�@�C��
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
/// <param name="tag">���</param>
/// <param name="name">����</param>
ComponentsBace::ComponentsBace(Tags tag, const std::string& name) noexcept
	: m_Tag{ tag }
	, m_Name{ name }
{
}

/// <summary>
/// Destructor
/// </summary>
ComponentsBace::~ComponentsBace() noexcept = default;
