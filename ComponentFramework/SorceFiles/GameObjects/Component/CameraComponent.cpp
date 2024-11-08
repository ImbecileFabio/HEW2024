//==================================================
// [CameraComponent.c@@] �J�����R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include "../../StdAfx.h"
#include "CameraComponent.h"

#include "../../GameProcess.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "TransformComponent.h"

/*----- �l�[���X�y�[�X -----*/
using namespace DirectX::SimpleMath;

/*----- �O���[�o���ϐ� -----*/
Vector3 g_pos;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CameraComponent::CameraComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CameraComponent::~CameraComponent()
{
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void CameraComponent::Init()
{
	TransformComponent* transform = owner_->GetComponent<TransformComponent>();

	g_pos = transform->GetPosition();

	g_pos = Vector3(10.f, 0.f, 0.f);
	target_ = Vector3(0.f, 0.f, 0.f);

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void CameraComponent::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void CameraComponent::Update()
{
	// �r���[�ϊ��s��쐬
	Vector3 up = Vector3(0.f, 1.f, 0.f);
	// ����n�ɕύX
	view_matrix_ = DirectX::XMMatrixLookAtLH(g_pos, target_, up);

	Renderer::SetViewMatrix(&view_matrix_);

	// �v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.f);

	float aspectRatio = static_cast<float>(GameProcess::GetWidth()) / static_cast<float>(GameProcess::GetHeight());	// �A�X��
	float nearPlane = 1.f;		// �j�A�N���b�v
	float farPlane = 1000.f;	// �t�@�[�N���b�v

	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

