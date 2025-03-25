/**
 * @file   SceneBace.h
 *
 * @brief  �V�[���̊��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/06
 */

#pragma once

#include <string>
#include "DeviceResources.h"

class SceneManager;
class ObjectBace;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBace
{
protected:
	// �V�[���}�l�[�W���ւ̃|�C���^
	SceneManager* mp_SceneManager;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// ���ʃX�e�[�g
	DirectX::CommonStates* mp_States;

public:
	/*���C���V�X�e��*/
	        SceneBace
			(
				SceneManager* pSceneManager,
				DX::DeviceResources* pDeviceResources,
				DirectX::SimpleMath::Matrix* pProj,
				DirectX::CommonStates* pStates
			) noexcept(false);
	virtual ~SceneBace () noexcept;
	virtual void Initialize (                       ) = 0;
	virtual void Update     (const float elapsedTime) = 0;
	virtual void Render     (                       ) = 0;
	virtual void Finalize   (                       ) = 0;

	/*�擾*/
	DX::DeviceResources* GetDeviceResourcesPointer() { return mp_DeviceResources; }
	DirectX::SimpleMath::Matrix* GetProjPointer()    { return mp_Proj; }
	DirectX::CommonStates* GetCommonStatesPointer()  { return mp_States; }
	SceneManager* GetSceneManagerPtr();

public:
	/*��������*/
	// �V�[���̕ύX
	void ChangeScene(const std::string& nextSceneName) noexcept(false);

	// ���L�f�[�^�̓ǂݍ���
	void ReadSharedData (const std::string& key, int*         pValue) const noexcept(false);
	void ReadSharedData (const std::string& key, float*       pValue) const noexcept(false);
	void ReadSharedData (const std::string& key, std::string* pValue) const noexcept(false);

	// ���L�f�[�^�ւ̏�������
	void WriteSharedData (const std::string& key, int         value) noexcept(false);
	void WriteSharedData (const std::string& key, float       value) noexcept(false);
	void WriteSharedData (const std::string& key, std::string value) noexcept(false);

protected:
	// �I�u�W�F�N�g�̒ǉ�
	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object) noexcept(false);

	// �I�u�W�F�N�g�ւ̃|�C���^�̎擾
	ObjectBace* GetObjectPtr(const std::string& objectName);
};

