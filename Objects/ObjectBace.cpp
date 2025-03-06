/**
 * @file   ObjectBace.cpp
 *
 * @brief  �I�u�W�F�N�g���N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "ObjectBace.h"

#include "../Managers/ObjectManager.h"
#include "../Scenes/SceneBace.h"
#include "../Managers/SceneManager.h" 

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectBace::ObjectBace(SceneBace* pScene) noexcept
	: mp_ObjectManager{ pScene->GetSceneManagerPtr()->GetObjectManagerPtr() }
	, mp_Scene        { pScene }
{
	m_Transform = std::make_unique<Transform>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectBace::~ObjectBace() noexcept
{
	mp_ObjectManager = nullptr;
	mp_Scene = nullptr;
	m_Transform.reset();
}

