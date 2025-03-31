/**
 * @file   Sound.cpp
 *
 * @brief  �T�E���h�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/31
 */

#include "pch.h"
#include "Sound.h"

/// <summary>
/// Constructor
/// </summary>
Sound::Sound(const std::string& name, DirectX::AudioEngine* pAudioEngine, const wchar_t* soundPath) noexcept:
	ComponentsBace{ Tags::NONE, name }
{
	m_SoundDate = std::make_unique<DirectX::SoundEffect>(pAudioEngine, soundPath);
}

/// <summary>
/// Destructor
/// </summary>
Sound::~Sound() noexcept
{
	m_SoundDate.reset();
}

/// <summary>
/// �T�E���h�̍Đ��֐�
/// </summary>
void Sound::Play()
{
	m_SoundDate->Play();
}
