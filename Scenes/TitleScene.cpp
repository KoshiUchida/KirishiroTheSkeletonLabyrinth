/**
 * @file   TitleScene.cpp
 *
 * @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/03/26
 */

#include "pch.h"
#include "TitleScene.h"

 // �O���錾
#include "Camera.h"

using namespace std;
using namespace DirectX;

// �{�^����������悤�ɂȂ�܂ł̎���
static constexpr float ButtonEnableTime = 1.0f;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene(SceneManager* sceneManager, DX::DeviceResources* pDeviceResources, DirectX::SimpleMath::Matrix* pProj, DirectX::CommonStates* pStates, DX::StepTimer* pTimer) noexcept(false):
	SceneBace(sceneManager, pDeviceResources, pProj, pStates),
	mp_timer{ pTimer },
	m_buttonEnableTime{ ButtonEnableTime },
	m_nowTime{ 0.0f },
	m_leftBackWheelBone(ModelBone::c_Invalid),
	m_rightBackWheelBone(ModelBone::c_Invalid),
	m_leftFrontWheelBone(ModelBone::c_Invalid),
	m_rightFrontWheelBone(ModelBone::c_Invalid),
	m_leftSteerBone(ModelBone::c_Invalid),
	m_rightSteerBone(ModelBone::c_Invalid),
	m_turretBone(ModelBone::c_Invalid),
	m_cannonBone(ModelBone::c_Invalid),
	m_hatchBone(ModelBone::c_Invalid)
{
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	m_Camera = make_unique<Camera>(SimpleMath::Vector3(9.0f, 7.0f, 9.0f));

	auto device = mp_DeviceResources->GetD3DDevice();

	m_nowTime = 0.0f;

	m_fxFactory = make_unique<EffectFactory>(device);

	m_fxFactory->SetDirectory(L"Resources\\Textures");

	m_model = Model::CreateFromSDKMESH(device, L"Resources\\Models\\Tank.sdkmesh",
		*m_fxFactory,
		ModelLoader_CounterClockwise | ModelLoader_IncludeBones);

	const size_t nbones = m_model->bones.size();

	m_drawBones = ModelBone::MakeArray(nbones);
	m_animBones = ModelBone::MakeArray(nbones);

	m_model->CopyBoneTransformsTo(nbones, m_animBones.get());

	uint32_t index = 0;
	for (const auto& it : m_model->bones)
	{
		if (_wcsicmp(it.name.c_str(), L"tank_geo") == 0)
		{
			m_animBones[index] = XMMatrixIdentity();
		}
		else if (_wcsicmp(it.name.c_str(), L"l_back_wheel_geo") == 0) { m_leftBackWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_back_wheel_geo") == 0) { m_rightBackWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"l_front_wheel_geo") == 0) { m_leftFrontWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_front_wheel_geo") == 0) { m_rightFrontWheelBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"l_steer_geo") == 0) { m_leftSteerBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"r_steer_geo") == 0) { m_rightSteerBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"turret_geo") == 0) { m_turretBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"canon_geo") == 0) { m_cannonBone = index; }
		else if (_wcsicmp(it.name.c_str(), L"hatch_geo") == 0) { m_hatchBone = index; }


		++index;
	}

#if defined(_DEBUG)
	auto context = mp_DeviceResources->GetD3DDeviceContext();

	/*�f�o�b�O���̒ǉ�����������*/
	// �f�o�b�O�t�H���g�̍쐬
	m_debugFont = make_unique<Imase::DebugFont>(device
		, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	// �O���b�h���̍쐬
	m_gridFloor = make_unique<Imase::GridFloor>(device, context, mp_States);
#endif
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���[s]</param>
void TitleScene::Update(const float elapsedTime)
{
	// �J�����X�V
	m_Camera->Update();

	m_nowTime += elapsedTime;

	m_world = SimpleMath::Matrix::CreateScale(0.01f);
	m_world *= SimpleMath::Matrix::CreateRotationY(m_nowTime * 0.1f);
	m_world *= SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	
	float wheelRotation = m_nowTime * 5.f;
	float steerRotation = sinf(m_nowTime * 0.75f) * 0.5f;
	float turretRotation = sinf(m_nowTime * 0.333f) * 1.25f;
	float cannonRotation = sinf(m_nowTime * 0.25f) * 0.333f - 0.333f;
	float hatchRotation = std::min(0.f, std::max(sinf(m_nowTime * 2.f) * 2.f, -1.f));

	XMMATRIX mat = XMMatrixRotationX(wheelRotation);
	m_animBones[m_leftFrontWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftFrontWheelBone]);
	m_animBones[m_rightFrontWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightFrontWheelBone]);
	m_animBones[m_leftBackWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftBackWheelBone]);
	m_animBones[m_rightBackWheelBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightBackWheelBone]);

	mat = XMMatrixRotationX(steerRotation);
	m_animBones[m_leftSteerBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_leftSteerBone]);
	m_animBones[m_rightSteerBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_rightSteerBone]);

	mat = XMMatrixRotationY(turretRotation);
	m_animBones[m_turretBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_turretBone]);

	mat = XMMatrixRotationX(cannonRotation);
	m_animBones[m_cannonBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_cannonBone]);

	mat = XMMatrixRotationX(hatchRotation);
	m_animBones[m_hatchBone] = XMMatrixMultiply(mat,
		m_model->boneMatrices[m_hatchBone]);

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ����炷
	m_buttonEnableTime -= elapsedTime;

	// �����A�{�^����������悤�ɂȂ�܂ł̎��Ԃ�0���傫�������ۂ̑������^�[��
	if (m_buttonEnableTime > 0.f) return;

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ�0�ɂ���
	m_buttonEnableTime = 0.f;

	// �L�[�{�[�h�̎擾
	Keyboard::State kd = Keyboard::Get().GetState();

	// �����AZ�L�[��������Ă��āA�{�^�����������悤�ɂȂ��Ă�����Q�[���v���C�V�[���ɑJ��
	if (kd.Z && m_buttonEnableTime <= 0.f)
		// �V�[���̑J��
		ChangeScene("Gameplay");
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{
	// �f�o�b�O�J��������r���[�s����擾����
	SimpleMath::Matrix view = m_Camera->GetCameraMatrix();

	// �R���e�L�X�g�̎擾
	auto context = mp_DeviceResources->GetD3DDeviceContext();
	size_t nbones = m_model->bones.size();

	m_model->CopyAbsoluteBoneTransforms(nbones,
		m_animBones.get(), m_drawBones.get());

	m_model->Draw(context, *mp_States, nbones, m_drawBones.get(),
		m_world, view, *mp_Proj);

#if defined(_DEBUG)
	/*�f�o�b�O�\��*/

	// �O���b�h�̏��̕`��
	m_gridFloor->Render(context, view, *mp_Proj);

	// �V�[�����̕\��
	m_debugFont->AddString(0, 0, Colors::White, L"Scene=Title");

	// FPS���擾����
	uint32_t fps = mp_timer->GetFramesPerSecond();

	// FPS�̕\��
	m_debugFont->AddString(0, 15, Colors::White, L"FPS=%d", fps);

	// �f�o�b�O�t�H���g�̕`��
	m_debugFont->Render(mp_States);
#endif
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	m_Camera.reset();

	m_fxFactory.reset();
	m_model.reset();

#if defined(_DEBUG)
	/*�f�o�b�O���̒ǉ��I������*/
	m_debugFont.reset();
	m_gridFloor.reset();
#endif
}
