/**
 * @file   Sound.h
 *
 * @brief  �T�E���h�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#pragma once
#include "ComponentsBace.h"

/// <summary>
/// �T�E���h�R���|�l�[�g�N���X
/// </summary>
class Sound :
    public ComponentsBace
{
private:
	// Sound Data
	std::unique_ptr<DirectX::SoundEffect> m_SoundDate;

public:
    /*Main System*/
	Sound(const std::string& name, DirectX::AudioEngine* pAudioEngine, const wchar_t* soundPath) noexcept;
	~Sound() noexcept;

	void Play();
};

