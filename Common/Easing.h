/**
 * @file   Easing.h
 *
 * @brief  �C�[�W���O���܂Ƃ߂��w�b�_�[�t�@�C��
 *
 * @author CatCode
 * 
 * �ȉ��̃T�C�g���Q�l�ɂ��č쐬����܂����B
 * https://easings.net/ja
 */

#pragma once

/// <summary>
/// �C�[�Y�A�E�g�N�C���g
/// </summary>
/// <param name="x">-1.0f ~ 1.0f</param>
float EaseOutQuint(float x);

/// <summary>
/// �C�[�Y�A�E�g�N�C���g
/// </summary>
/// <param name="max">�ő�l</param>
/// <param name="min">�ŏ��l</param>
float EaseOutQuint(float max, float min, float x);

/// <summary>
/// �C�[�X�C���A�E�g�T�C��
/// </summary>
/// <param name="x">-1.0f ~ 1.0f</param>
float EaseInOutSine(float x);

/// <summary>
/// �C�[�X�C���A�E�g�T�C��
/// </summary>
/// <param name="max">�ő�l</param>
/// <param name="min">�ŏ��l</param>
float EaseInOutSine(float max, float min, float x);
