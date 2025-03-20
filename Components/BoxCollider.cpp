/**
 * @file   BoxCollider.cpp
 *
 * @brief  ボックスコライダークラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/03/18
 */

#include "pch.h"
#include "BoxCollider.h"

// 前方宣言
#include "Transform.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
BoxCollider::BoxCollider(SceneBace* pScene, const std::string& name, Transform* pTransform, const DirectX::SimpleMath::Vector3& siz, bool canDraw) noexcept(false)
	: ColliderBace(pScene, ColliderType::Box, name, pTransform, canDraw, SimpleMath::Vector3())
	, m_Siz{ siz }
	, m_Positions{}
{
	AddSiz(&m_Positions, m_Siz);

#if defined(_DEBUG)
	// モデルの作成
	m_Model = GeometricPrimitive::CreateBox(mp_DeviceResources->GetD3DDeviceContext(), siz * 5.f);
#endif
}

/// <summary>
/// Destructor
/// </summary>
BoxCollider::~BoxCollider() noexcept = default;

/// <summary>
/// 重なり判定
/// </summary>
bool BoxCollider::Collider(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Box:
		if (true)
		{
			Positions InsertBox = m_Positions;

			AddSiz(&InsertBox, static_cast<BoxCollider*>(other)->GetSiz());

			MovePositions(&InsertBox, this->GetPosition());

			SimpleMath::Vector3 findPosiiton = other->GetPosition();

			return(
				(InsertBox.min.x <= findPosiiton.x && findPosiiton.x <= InsertBox.max.x) &&
				(InsertBox.min.y <= findPosiiton.y && findPosiiton.y <= InsertBox.max.y) &&
				(InsertBox.min.z <= findPosiiton.z && findPosiiton.z <= InsertBox.max.z));
		}
	case ColliderType::Sphare:

	default:
		return false;
	}
}

/// <summary>
/// 押し出し処理関数
/// </summary>
/// <param name="other">加押し出し処理コライダー</param>
void BoxCollider::Collision(ColliderBace* other)
{
	switch (other->GetType())
	{
	case ColliderType::Box:
		// BoxCollider同士の押し出し処理
		if (true)
		{
			// 重なりを調べる
			if (!Collider(other)) return;

			// 中心座標同士の座標の差分を取得
			SimpleMath::Vector3 diffPosition = other->GetPosition() - mp_Transform->GetPosition();

			// 縦軸角度を取得
			float vertical{ 0.f };

			// ZまたはXの値が0だった場合は値を求めない
			if (diffPosition.z != 0.f && diffPosition.x != 0.f)
				vertical = atan2f(diffPosition.z, diffPosition.x) * 180.f / XM_PI;

			// 横軸角度を取得
			float horizontal{ 0.f };

			// YまたはXの値が0だった場合は値を求めない
			if(diffPosition.y != 0.f && diffPosition.x != 0.f)
				horizontal = atan2f(diffPosition.y, diffPosition.x) * 180.f / XM_PI;

			enum class Face
			{
				top,
				buttom,
				left,
				right,
				front,
				back
			};

			Face face;

			// 縦軸から方向を予測
			if (vertical == 0.f)
				face = Face::front;
			else if (-45.f <= vertical && vertical <= 45.f)
				face = Face::left;
			else if (45.f <= vertical && vertical <= 135.f)
				face = Face::back;
			else if (-45.f >= vertical && vertical >= -135.f)
				face = Face::front;
			else
				face = Face::right;

			// 横軸の方向から必要であったら方向を変更
			if (45.f <= horizontal && horizontal <= 135.f)
				face = Face::top;
			else if (-45.f >= horizontal && horizontal >= -135.f)
				face = Face::buttom;

			// 加力コライダーのサイズを取得
			SimpleMath::Vector3 otherSiz = static_cast<BoxCollider*>(other)->GetSiz();

			// 方向別に押し出す
			switch (face)
			{
			case Face::top:
				// 上方向
				mp_Transform->SetPositionY(other->GetPosition().y + otherSiz.y + m_Siz.y + 0.001f);
				break;
			case Face::buttom:
				// 下方向
				mp_Transform->SetPositionY(other->GetPosition().y - otherSiz.y - m_Siz.y - 0.001f);
				break;
			case Face::left:
				// 左方向
				mp_Transform->SetPositionX(other->GetPosition().x - otherSiz.x - m_Siz.x - 0.001f);
				break;
			case Face::right:
				// 右方向
				mp_Transform->SetPositionX(other->GetPosition().x + otherSiz.x + m_Siz.x + 0.001f);
				break;
			case Face::front:
				// 前方
				mp_Transform->SetPositionZ(other->GetPosition().z + otherSiz.z + m_Siz.z + 0.001f);
				break;
			case Face::back:
				// 後方
				mp_Transform->SetPositionZ(other->GetPosition().z - otherSiz.z - m_Siz.z - 0.001f);
				break;
			default:
				// ERORR
				break;
			}

			break;
		}
	case ColliderType::Sphare:
		// ToDo : 球との押し出し処理
		break;
	default:
		break;
	}

	return;
}

/// <summary>
/// サイズの取得
/// </summary>
DirectX::SimpleMath::Vector3 BoxCollider::GetSiz() const
{
	return m_Siz;
}
