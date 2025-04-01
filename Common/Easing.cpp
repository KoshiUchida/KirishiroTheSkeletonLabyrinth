/**
 * @file   Easing.cpp
 *
 * @brief  �C�[�W���O���܂Ƃ߂��\�[�X�t�@�C��
 *
 * @author CatCode
 * 
 * �ȉ��̃T�C�g���Q�l�ɂ��č쐬����܂����B
 * https://easings.net/ja
 */

#include "pch.h"
#include "Easing.h"

float EaseOutQuint(float x)
{
    return 1.f - std::powf(1.f - x, 5.f);
}

float EaseOutQuint(float max, float min, float x)
{
    return EaseOutQuint((x - min) / (max - min));
}

float EaseInOutSine(float x)
{
    return -(std::cosf(DirectX::XM_PI * x) - 1.f) / 2.f;
}

float EaseInOutSine(float max, float min, float x)
{
    return EaseInOutSine((x - min) / (max - min));
}
