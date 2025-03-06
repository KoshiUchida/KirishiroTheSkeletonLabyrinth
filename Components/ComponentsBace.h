/**
 * @file   ComponentsBace.h
 *
 * @brief  �R���|�[�g���N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/04
 */

#pragma once

/// <summary>
/// �R���|�[�l���g���N���X
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

