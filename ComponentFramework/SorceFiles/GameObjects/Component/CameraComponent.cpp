//==================================================
// [CameraComponent.c@@] �J�����R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "CameraComponent.h"
#include "../../GameProcess.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "TransformComponent.h"

/*----- �l�[���X�y�[�X -----*/
using namespace DirectX::SimpleMath;


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CameraComponent::CameraComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	std::format("��CamelaComponent�� -> Constructor\n");


	target_ = Vector3(0.f, 0.f, 0.f);

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CameraComponent::~CameraComponent()
{
	std::cout << std::format("��CamelaComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void CameraComponent::Init()
{

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
	auto transform = owner_->GetComponent<TransformComponent>();
	if (transform)
	{
		auto pos = transform->GetPosition();
		view_matrix_ = DirectX::XMMatrixLookAtLH(pos, target_, up);
	}
	else
	{
		std::cout << std::format("��CameraComponent�� -> Default Position\n");
		view_matrix_ = DirectX::XMMatrixLookAtLH(Vector3(0.f, 0.f, -900.f), Vector3(0.f, 0.f, 0.f), up);
	}

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

