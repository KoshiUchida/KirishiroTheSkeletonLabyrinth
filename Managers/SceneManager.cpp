/**
 * @file   SceneManaager.cpp
 *
 * @brief  �V�[���̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#include "pch.h"
#include "SceneManager.h"

// �R���X�g���N�^
SceneManager::SceneManager()
	: m_pCurrentScene  { nullptr }
	, m_pRequestedScene{ nullptr }
	, m_scenes         {}
	, m_IsEnd          {}
{
	m_ObjectManager = std::make_unique<ObjectManager>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();

	m_ObjectManager.reset();
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update(const float elapsedTime)
{
	// �V�[���̕ύX�v�����������ꍇ�̓V�[���̕ύX���s��
	if (m_pRequestedScene)
	{
		ChangeScene();
	}

	// ���݂̃V�[�����X�V
	if (m_pCurrentScene)
		m_pCurrentScene->Update(elapsedTime);

	// �I�u�W�F�N�g�̍X�V
	m_ObjectManager->Update(elapsedTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	// ���݂̃V�[����`��
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

/// <summary>
/// �V�[���̓o�^
/// </summary>
/// <param name="sceneName">�V�[���̓o�^��</param>
/// <param name="scene">�o�^�V�[��</param>
void SceneManager::addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/// <summary>
/// �J�n�V�[���̐ݒ�
/// </summary>
/// <param name="startSceneName">�J�n�V�[����</param>
void SceneManager::SetStartScene(const std::string& startSceneName)
{
	RequestSceneChange(startSceneName);
}

/// <summary>
/// �V�[���ύX�̗v��
/// </summary>
/// <param name="changeSceneName">�ύX�\��̃V�[����</param>
void SceneManager::RequestSceneChange(const std::string& changeSceneName)
{
	if (changeSceneName == "End")
	{
		m_IsEnd = true;
		return;
	}

	if (m_scenes.count(changeSceneName) == 0)
	{
		// Error
		return;
	}

	m_pRequestedScene = m_scenes[changeSceneName].get();
}

/// <summary>
/// �I�u�W�F�N�g�̒ǉ�
/// </summary>
/// <param name="objectName">�ǉ�����I�u�W�F�N�g��</param>
/// <param name="object">�ǉ�����I�u�W�F�N�g</param>
void SceneManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	m_ObjectManager->AddObject(objectName, std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g�̃|�C���^�擾
/// </summary>
/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
/// <returns></returns>
ObjectBace* SceneManager::GetObjectPtr(const std::string& objectName)
{
	return m_ObjectManager->GetObjectPtr(objectName);
}

/// <summary>
/// ���L�f�[�^�̎擾
/// </summary>
/// <param name="key">�擾���������L�f�[�^�̃L�[</param>
/// <returns>�L�[�̋��L�f�[�^</returns>
std::string SceneManager::GetShareData(const std::string& key) const
{
	if (m_shareData.count(key) == 0)
	{
		// Error
		return std::string{};
	}

	return m_shareData.at(key);
}

ObjectManager* SceneManager::GetObjectManagerPtr()
{
	return m_ObjectManager.get();
}

/// <summary>
/// ���L�f�[�^�̐ݒ�
/// </summary>
/// <param name="key">�ݒ肵�������L�f�[�^�̃L�[</param>
/// <param name="value">�ݒ肵�������L�f�[�^�̒l</param>
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_shareData[key] = value;
}

/// <summary>
/// �V�[���̕ύX
/// </summary>
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
		return;

	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();
	
	m_ObjectManager->Finalize();

	if (m_IsEnd)
		return;

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();

	m_pRequestedScene = nullptr;
}
