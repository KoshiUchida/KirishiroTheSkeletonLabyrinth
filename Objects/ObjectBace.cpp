/**
 * @file   ObjectBace.cpp
 *
 * @brief  �I�u�W�F�N�g���N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Scenes/SceneBace.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_Scene{ pScene }
{
	m_Transform = std::make_unique<Transform>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_Scene = nullptr;
	m_Transform.reset();
}
