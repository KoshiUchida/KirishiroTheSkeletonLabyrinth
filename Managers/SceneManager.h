/**
 * @file   SceneManaager.h
 *
 * @brief  �V�[���̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

/** ���ӎ���
* �EObjectManager�ɂ���
*    �I�u�W�F�N�g�̒ǉ��̍ۂ́A�K���V�[���̏����������̏��ɏ����悤��
*/

#pragma once
#include "ObjectManager.h"

#include <unordered_map>
#include <string>
#include <memory>

#include "../Scenes/SceneBace.h"

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
private:
	// �G�C���A�X�錾
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<SceneBace>>;
	using ShareData       = std::unordered_map<std::string, std::string>;

	// �V�[���̏W����
	SceneCollection m_scenes;

	// ���݂̃V�[��
	SceneBace* m_pCurrentScene;
	// �ύX�v���̂������V�[��
	SceneBace* m_pRequestedScene;

	// ���L�f�[�^
	ShareData m_shareData;

	// �I������
	bool m_IsEnd;

	// Object Manager
	std::unique_ptr<ObjectManager> m_ObjectManager;

public:
	/*���C���V�X�e��*/
	SceneManager  ();
	~SceneManager ();
	void Update (const float elapsedTime);
	void Render ();

	// �V�[���̓o�^
	void addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene);

	// �N�����̃V�[���̐ݒ�
	void SetStartScene(const std::string& startSceneName);

	// �V�[���ύX�̗v��
	void RequestSceneChange(const std::string& changeSceneName);

	// �I�u�W�F�N�g�̒ǉ�
	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	// �I�u�W�F�N�g�̎Q��
	ObjectBace* GetObjectPtr(const std::string& objectName);

	/*�擾/�ݒ�*/
	// ���L�f�[�^�̎擾
	std::string GetShareData(const std::string& key) const;

	// �I�����߂̎擾
	bool isEnd() const { return m_IsEnd; }

	// �I�u�W�F�N�g�}�l�[�W���ւ̃|�C���^�̎擾
	ObjectManager* GetObjectManagerPtr();

	// ���L�f�[�^�̐ݒ�
	void SetSharedData(const std::string& key, const std::string& value);

private:
	// �V�[���̕ύX
	void ChangeScene();

};

