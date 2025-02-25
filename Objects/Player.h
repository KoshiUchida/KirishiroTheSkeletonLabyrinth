/**
 * @file   Player.h
 *
 * @brief  �v���C���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/25
 */

#pragma once
#include <memory>
#include "DeviceResources.h"
#include "Transform.h"

class SceneBace;

/// <summary>
/// 3D���f���`��N���X
/// </summary>
class Renderer3D
{
private:
	// �g�����X�t�H�[���ւ̃|�C���^
	Transform* mp_Transform;

	// ���f��
	std::unique_ptr<DirectX::Model> m_Model;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// ���ʃX�e�[�g
	DirectX::CommonStates* mp_States;

public:
	Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false);
	~Renderer3D() noexcept;
	void Draw(const DirectX::SimpleMath::Matrix& view);
};

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
private:
	// �g�����X�t�H�[��
	Transform m_Transform;

	// �����_���[
	Renderer3D m_Renderer;

public:
	// Main System
	Player(SceneBace* pScene) noexcept(false);
	~Player() noexcept;

	void Initialize();
	void Update(float elapsedTime);

	Transform* GetTransformPointer() { return &m_Transform; }
	Renderer3D* GetRenderer3DPointer() { return &m_Renderer; }
};

