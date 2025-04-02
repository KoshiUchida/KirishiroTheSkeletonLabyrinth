/**
 * @file   Transform2D.h
 *
 * @brief  �Q�����g�����X�t�H�[���̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/02
 */

#pragma once
#include "ComponentsBace.h"

#include "DeviceResources.h"

/// <summary>
/// �Q�����g�����X�t�H�[���R���|�l�[�g�N���X
/// </summary>
class Transform2D :
	public ComponentsBace
{
public:
	/// <summary>
	/// �X�N���[����̒��S���W
	/// </summary>
	enum class ScreenOrigin
	{
		Up,
		Down,
		Left,
		Right,
		UpRight,
		UpLeft,
		DownRight,
		DownLeft,
	};

private:
	// ���W
	DirectX::SimpleMath::Vector2 m_Position;
	
	// ��]
	float m_Rotate;
	
	// �傫��
	DirectX::SimpleMath::Vector2 m_Scale;

	// �X�N���[����̒��S���W
	ScreenOrigin m_Origin;

public:
	/*Main System*/
	Transform2D(DirectX::SimpleMath::Vector2 position = DirectX::SimpleMath::Vector2::Zero, float rotate = 0.f, DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2(1.f, 1.f), ScreenOrigin origin = ScreenOrigin::UpLeft);
	~Transform2D();

	// Setter
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	void SetRotate(float rotate);
	void SetScale(float scale);
	void SetOrigin(ScreenOrigin origin);

	void SetPositionX(float x);
	void SetPositionY(float y);

	// Getter
	DirectX::SimpleMath::Vector2 GetPosition() const;
	DirectX::SimpleMath::Vector2 GetPosition(DX::DeviceResources* pDevice);
	
	float GetRotate() const;
	DirectX::SimpleMath::Vector2 GetScale () const;

	float GetPositionX() const;
	float GetPositionY() const;
};

