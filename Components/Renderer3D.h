/**
 * @file   Renderer3D.h
 *
 * @brief  ���f���`��R���|�[�l���g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/17
 */

#pragma once
#include "RendererBace.h"
#include <memory>
#include "DeviceResources.h"

class Transform;
class SceneBace;

/// <summary>
/// 3D���f���`��N���X
/// </summary>
class Renderer3D
	: public RendererBace
{
public:
	// ���f���̓ǂݍ��݌`��
	enum class Read
	{
		SDK,
		CMO
	};

private:
	// �g�����X�t�H�[���ւ̃|�C���^
	Transform* mp_Transform;

	// ���f��
	std::unique_ptr<DirectX::Model> m_Model;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

public:
	Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath, Read read = Read::SDK) noexcept(false);
	~Renderer3D() noexcept;
	void Draw(const DirectX::SimpleMath::Matrix& view) override final;
};

