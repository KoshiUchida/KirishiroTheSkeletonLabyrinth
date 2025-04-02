/**
 * @file   Renderer3DWithAnimation.h
 *
 * @brief  �A�j���[�V�����t��3���������_���[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/03
 */

#pragma once
#include "ComponentsBace.h"

#include <memory>
#include <unordered_map>
#include "DeviceResources.h"
#include "Animation.h"

class Transform;
class SceneBace;

/// <summary>
/// �A�j���[�V�����t��3���������_���[�R���|�l�[�g�N���X
/// </summary>
class Renderer3DWithAnimation :
    public ComponentsBace
{
private:
    // ���ʃX�e�[�g
    DirectX::CommonStates* mp_States;

	// �f�o�C�X���\�[�X�ւ̃|�C���^
	DX::DeviceResources* mp_DeviceResources;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix* mp_Proj;

	// �g�����X�t�H�[���ւ̃|�C���^
	Transform* mp_Transform;

	// ���f��
	std::unique_ptr<DirectX::Model> m_Model;

	// ���f���̃{�[��
	DirectX::ModelBone::TransformArray m_drawBones;

	// �A�j���[�V�����Q
	DX::AnimationSDKMESH m_Animation;

public:
    /*Main System*/
    Renderer3DWithAnimation(SceneBace* pScene, std::string name, Transform* pTransform, const wchar_t* modelPath) noexcept;
    ~Renderer3DWithAnimation() noexcept;

	void SetAnimation(const wchar_t* animationPath);

	void Update(float elapseTime);
	void Draw(const DirectX::SimpleMath::Matrix& view);
};

