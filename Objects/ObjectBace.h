/**
 * @file   ObjectBace.h
 *
 * @brief  �I�u�W�F�N�g���N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class ObjectManager;
class SceneBace;
class ComponentsBace;

/// <summary>
/// �I�u�W�F�N�g�̊��N���X
/// </summary>
class ObjectBace
{
protected:
	// �G�C���A�X�錾
	using ComponentsCollection = std::unordered_map<std::string, std::unique_ptr<ComponentsBace>>;

	// �I�u�W�F�N�g�}�l�[�W���ւ̃|�C���^
	ObjectManager* mp_ObjectManager;

	// �V�[���ւ̃|�C���^
	SceneBace* mp_Scene;

	// �R���|�l�[�g�̏W��
	ComponentsCollection m_Components;

	// �I�u�W�F�N�g�̖��O
	std::string m_Name;

	// ���C���[
	int m_Layer;

public:
	// Constructor & Destructor
	ObjectBace(SceneBace* pScene, const std::string& name) noexcept;
	virtual ~ObjectBace() noexcept;

	// Main System
	virtual void Initialize(                 ) = 0;
	virtual void Process   (float elapsedTime) = 0;
	void Update(float elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& view);

	void AddComponent(std::unique_ptr<ComponentsBace> component);

	void SetLayer(int layer);

	ComponentsBace* GetComponentPtr(const std::string& name);
	ObjectBace* GetObjectPtr(const std::string& name);
	std::string GetName() const noexcept;
	int GetLayer() const noexcept;
};

