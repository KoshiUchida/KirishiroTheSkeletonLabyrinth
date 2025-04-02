/**
 * @file   TitleScene.cpp
 *
 * @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/02
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
	m_nowTime{ 0.0f }
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

	m_model = Model::CreateFromSDKMESH(device, L"Resources\\Models\\Kirishiro.sdkmesh",
		*m_fxFactory,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);

	DX::ThrowIfFailed(
		m_animation.Load(L"Resources\\Models\\KirishiroIdol.sdkmesh_anim")
	);

	m_animation.Bind(*m_model);

	m_drawBones = ModelBone::MakeArray(m_model->bones.size());

	m_model->UpdateEffects([&](IEffect* effect)
		{
			auto skin = dynamic_cast<SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		}
	);


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

	m_animation.Update(elapsedTime);

	m_nowTime += elapsedTime;

	m_world = SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ����炷
	m_buttonEnableTime -= elapsedTime;

	// �����A�{�^����������悤�ɂȂ�܂ł̎��Ԃ�0���傫�������ۂ̑������^�[��
	if (m_buttonEnableTime > 0.f) return;

	// �{�^����������悤�ɂȂ�܂ł̎��Ԃ�0�ɂ���
	m_buttonEnableTime = 0.f;

	// �L�[�{�[�h�̎擾
	Keyboard::State kb = Keyboard::Get().GetState();

	// �����A��������̃A�N�V�����L�[��������Ă��āA�{�^�����������悤�ɂȂ��Ă�����Q�[���v���C�V�[���ɑJ��
	if ((kb.C || kb.I || kb.X || kb.K || kb.Z || kb.J || kb.V || kb.L) && m_buttonEnableTime <= 0.f)
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

	m_animation.Apply(*m_model, nbones, m_drawBones.get());

	m_model->DrawSkinned(context, *mp_States, nbones, m_drawBones.get(),
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
