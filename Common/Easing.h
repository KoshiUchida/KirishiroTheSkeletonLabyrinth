/**
 * @file   Easing.h
 *
 * @brief  イージングをまとめたヘッダーファイル
 *
 * @author CatCode
 * 
 * 以下のサイトを参考にして作成されました。
 * https://easings.net/ja
 */

#pragma once

/// <summary>
/// イーズアウトクイント
/// </summary>
/// <param name="x">-1.0f ~ 1.0f</param>
float EaseOutQuint(float x);

/// <summary>
/// イーズアウトクイント
/// </summary>
/// <param name="max">最大値</param>
/// <param name="min">最小値</param>
float EaseOutQuint(float max, float min, float x);

/// <summary>
/// イースインアウトサイン
/// </summary>
/// <param name="x">-1.0f ~ 1.0f</param>
float EaseInOutSine(float x);

/// <summary>
/// イースインアウトサイン
/// </summary>
/// <param name="max">最大値</param>
/// <param name="min">最小値</param>
float EaseInOutSine(float max, float min, float x);
