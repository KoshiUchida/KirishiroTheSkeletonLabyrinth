/**
 * @file   Transform.cpp
 *
 * @brief  プレイヤーのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/24
 */

#include "pch.h"
#include "Player.h"
#include "../Scenes/SceneBace.h"

using namespace DirectX;

/// <summary>
/// コンストラクト
/// </summary>
Player::Player() noexcept
	: m_Transform{}
	, mp_DeviceResources{ nullptr }
	, mp_Proj{ nullptr }
	, mp_States{ nullptr }
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
	DirectX::CommonStates* pStates) noexcept(false)
	: Player()
{
	mp_DeviceResources = pDeviceResources;
	mp_Proj = pProj;
	mp_States = pStates;

	// モデルの読み込み
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
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
		m_Transform.AddPositionX(-1.5f * elapsedTime);
	}

	// 右キーが押されているか
	if (kd.Right)
	{
		m_Transform.AddPositionX(1.5f * elapsedTime);
	}

	// 上キーが押されているか  
	if (kd.Up)
	{
		m_Transform.AddPositionZ(-1.5f * elapsedTime);
	}

	// 下キーが押されているか
	if (kd.Down)
	{
		m_Transform.AddPositionZ(1.5f * elapsedTime);
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
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_Transform.GetPosition());

	// X軸で回転する行列を作成する
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_Transform.GetRotateX());

	// Y軸で回転する行列を作成する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_Transform.GetRotateY());

	// Z軸で回転する行列を作成する
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(m_Transform.GetRotateZ());

	// 拡大する行列を作成する
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_Transform.GetScale());

	// ワールド行列へ統合
	world = trans * rotZ * rotY * rotX * scale;

	// モデルの描画
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}


/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	m_Model.reset();
}

Renderer3D::Renderer3D(SceneBace* pScene, Transform* pTransform, const wchar_t* modelPath) noexcept(false)
	: mp_Transform      { pTransform }
	, mp_DeviceResources{ pScene->GetDeviceResourcesPointer() }
	, mp_Proj           { pScene->GetProjPointer() }
	, mp_States         { pScene->GetCommonStatesPointer() }
{
	// モデルの読み込み
	auto device = mp_DeviceResources->GetD3DDevice();
	EffectFactory fx(device);
	m_Model = Model::CreateFromSDKMESH(
		device, modelPath, fx);
}

Renderer3D::~Renderer3D() noexcept
{
	m_Model.reset();
}

void Renderer3D::Draw(const DirectX::SimpleMath::Matrix& view)
{
	// ワールド行列
	SimpleMath::Matrix world;

	// 平行移動する行列を作成する
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(mp_Transform->GetPosition());

	// X軸で回転する行列を作成する
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(mp_Transform->GetRotateX());

	// Y軸で回転する行列を作成する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateY());

	// Z軸で回転する行列を作成する
	SimpleMath::Matrix rotZ = SimpleMath::Matrix::CreateRotationY(mp_Transform->GetRotateZ());

	// 拡大する行列を作成する
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(mp_Transform->GetScale());

	// ワールド行列へ統合
	world = trans * rotZ * rotY * rotX * scale;

	// モデルの描画
	m_Model->Draw(
		mp_DeviceResources->GetD3DDeviceContext(),
		*mp_States, world, view, *mp_Proj);
}
