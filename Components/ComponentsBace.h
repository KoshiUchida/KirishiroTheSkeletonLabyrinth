/**
 * @file   ComponentsBace.h
 *
 * @brief  コンポート基底クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once

/// <summary>
/// コンポーネント基底クラス
/// </summary>
class ComponentsBace
{
public:
	enum class Tags
	{
		NONE,
		Update,
		Render
	};

private:
	Tags m_Tag;
	std::string m_Name;

public:
	ComponentsBace(Tags tag, const std::string& name) noexcept;
	virtual ~ComponentsBace() noexcept;

	     Tags   GetTag () const { return m_Tag; }
	std::string GetName() const { return m_Name; }
};

