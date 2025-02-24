/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#include "pch.h"
#include "Player.h"

using namespace DirectX;

/// <summary>
/// コンストラクト
/// </summary>
Player::Player() noexcept
	: m_position(0.0f, 0.0f, 0.0f)
	, m_rotate  (0.0f, 0.0f, 0.0f)
	, m_scale   (1.0f, 1.0f, 1.0f)
	, mp_DeviceResources{ nullptr }
	, mp_Proj           { nullptr }
	, mp_States         { nullptr }
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() noexcept = default;

/// <summary>
/// コンストラクト
/// </summary>
Player::Player(
	        DX::DeviceResources* pDeviceResources,
	DirectX::SimpleMath::Matrix* pProj,
	      DirectX::CommonStates* pStates)
	: Player()
{
	mp_DeviceResources = pDeviceResources;
	mp_Proj            = pProj;
	mp_States          = pStates;

	// モデルの読み込み
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_model = Model::CreateFromSDKMESH(
		device, L"Resources\\Models\\Kirishiro.sdkmesh", fx);
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(float elapsedTime)
{
	// キーボードの入力を取得
	auto kd = Keyboard::Get().GetState();

	//float rotateSpeed = 75.f;

	//// 速度ベクトル
	//SimpleMath::Vector3 v(0.0f, 0.0f, 3.0f);

	//// Y軸で回転する行列を作成する
	//SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);
	//v = SimpleMath::Vector3::Transform(v, rotY);

	// 左キーが押されているか
	if (kd.Left)
	{
		m_position.x += 3.0f * elapsedTime;
	}

	// 右キーが押されているか
	if (kd.Right)
	{
		m_position.x -= 3.0f * elapsedTime;
	}

	// 上キーが押されているか  
	if (kd.Up)
	{
		m_position.z += 3.0f * elapsedTime;
	}

	// 下キーが押されているか
	if (kd.Down)
	{
		m_position.z -= 3.0f * elapsedTime;
	}

	//m_position += v * 3.0f * elapsedTime;
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw(const SimpleMath::Matrix& view)
{
	// ワールド行列
	SimpleMath::Matrix world;

	// 平行移動する行列を作成する
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_position);

	// X軸で回転する行列を作成する
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_rotate.x);

	// Y軸で回転する行列を作成する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_rotate.y);

	// Z軸で回転する行列を作成する
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(m_rotate.z);

	// 拡大する行列を作成する
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_scale);

	// ワールド行列へ統合
	world = trans * rotZ * rotY * rotX * scale;

	// モデルの描画
	m_model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}


/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	m_model.reset();
}


/*Setter Functions*/

void Player::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

void Player::SetRotate(const DirectX::SimpleMath::Vector3& rotate)
{
	m_rotate = rotate;
}

void Player::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}

void Player::SetPositionX(float x)
{
	m_position.x = x;
}

void Player::SetPositionY(float y)
{
	m_position.y = y;
}

void Player::SetPositionZ(float z)
{
	m_position.z = z;
}

void Player::SetRotateX(float x)
{
	m_rotate.x = x;
}

void Player::SetRotateY(float y)
{
	m_rotate.y = y;
}

void Player::SetRotateZ(float z)
{
	m_rotate.z = z;
}

void Player::SetScaleX(float x)
{
	m_scale.x = x;
}

void Player::SetScaleY(float y)
{
	m_scale.y = y;
}

void Player::SetScaleZ(float z)
{
	m_scale.z = z;
}


/*Getter Functions*/

DirectX::SimpleMath::Vector3 Player::GetPosition() const
{
	return m_position;
}

DirectX::SimpleMath::Vector3 Player::GetRotate() const
{
	return m_rotate;
}

DirectX::SimpleMath::Vector3 Player::GetScale() const
{
	return m_scale;
}

float Player::GetPositionX() const
{
	return m_position.x;
}

float Player::GetPositionY() const
{
	return m_position.y;
}

float Player::GetPositionZ() const
{
	return m_position.z;
}

float Player::GetRotateX() const
{
	return m_rotate.x;
}

float Player::GetRotateY() const
{
	return m_rotate.y;
}

float Player::GetRotateZ() const
{
	return m_rotate.z;
}

float Player::GetScaleX() const
{
	return m_scale.x;
}

float Player::GetScaleY() const
{
	return m_scale.y;
}

float Player::GetScaleZ() const
{
	return m_scale.z;
}
