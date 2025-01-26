//==================================================
// [CameraComponent.cpp] �J�����R���|�[�l���g
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
	std::cout << std::format("��CamelaComponent�� -> Constructor\n");

	this->Init();
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
	target_ = Vector3(0.f, 0.f, 1.f);

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
	auto transform = owner_->GetTransformComponent();
	if (transform)
	{
		auto pos = transform->GetPosition();
		view_matrix_ = DirectX::XMMatrixLookAtLH(pos, target_, up);
	}
	else
	{
		std::cout << std::format("��CameraComponent�� -> Default Position\n");
		view_matrix_ = DirectX::XMMatrixLookAtLH(Vector3(0, 0, -1), Vector3(0.f, 0.f, 1.f), up);
	}

	Renderer::SetViewMatrix(&view_matrix_);

	// �v���W�F�N�V�����s��̐���
	float nearPlane = 1.0f;		// �j�A�N���b�v
	float farPlane = 1000.0f;	// �t�@�[�N���b�v

	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(GameProcess::GetWidth()), static_cast<float>(GameProcess::GetHeight()), nearPlane, farPlane);



	Renderer::SetProjectionMatrix(&projectionMatrix);
}