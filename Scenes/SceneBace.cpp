/**
 * @file   SceneBace.cpp
 *
 * @brief  �V�[���̊��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "SceneBace.h"

#include "../Managers/SceneManager.h"
#include "../Objects/ObjectBace.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="pSceneManager">�V�[���}�l�[�W���ւ̃|�C���^</param>
SceneBace::SceneBace
(
	               SceneManager* pSceneManager,
	        DX::DeviceResources* pDeviceResources,
	DirectX::SimpleMath::Matrix* pProj,
	      DirectX::CommonStates* pStates
) noexcept(false)
	: mp_SceneManager    { pSceneManager }
	, mp_DeviceResources { pDeviceResources }
	, mp_Proj            { pProj }
	, mp_States          { pStates }
{
}

/// <summary>
/// Destructor
/// </summary>
SceneBace::~SceneBace() noexcept = default;

/// <summary>
/// �V�[���̕ύX
/// </summary>
/// <param name="nextSceneName">�ύX��̃V�[����</param>
void SceneBace::ChangeScene(const std::string& nextSceneName) noexcept(false)
{
	mp_SceneManager->RequestSceneChange(nextSceneName);
}

/// <summary>
/// ���L�f�[�^�̓ǂݍ���
/// </summary>
/// <param name="key">���L�f�[�^�L�[</param>
/// <param name="pValue">�ǂݍ��ݐ�</param>
void SceneBace::ReadSharedData(const std::string& key, int* pValue) const noexcept(false)
{
	*pValue = std::stoi(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, float* pValue) const noexcept(false)
{
	*pValue = std::stof(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, std::string* pValue) const noexcept(false)
{
	*pValue = mp_SceneManager->GetShareData(key);
}

/// <summary>
/// ���L�f�[�^�ւ̏�������
/// </summary>
void SceneBace::WriteSharedData(const std::string& key, int value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, float value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, std::string value) noexcept(false)
{
	mp_SceneManager->SetSharedData(key, value);
}

/// <summary>
/// �I�u�W�F�N�g�̒ǉ�
/// </summary>
/// <param name="objectName">�ǉ�����I�u�W�F�N�g�̖��O</param>
/// <param name="object">�ǉ�����I�u�W�F�N�g</param>
void SceneBace::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object) noexcept(false)
{
	mp_SceneManager->AddObject(objectName, std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g�ւ̃|�C���^�̎擾
/// </summary>
/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
/// <returns>�I�u�W�F�N�g�ւ̃|�C���^</returns>
ObjectBace* SceneBace::GetObjectPtr(const std::string& objectName)
{
	return mp_SceneManager->GetObjectPtr(objectName);
}

SceneManager* SceneBace::GetSceneManagerPtr()
{
	return mp_SceneManager;
}

