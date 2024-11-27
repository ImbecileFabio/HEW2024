//==================================================
// [Camera.cpp] �J�����I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Camera.h"
#include "../Component/CameraComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Camera::Camera(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Camera�� -> new\n");

	// �J�����R���|�[�l���g
	camera_component_ = new CameraComponent(this, 0);

	transform_component_->SetPosition(0, 0, -1);
	
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Camera::~Camera()
{
	std::cout << std::format("��Camera�� -> delete\n");
	// �R���|�[�l���g�̍폜
	delete camera_component_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Camera::UpdateGameObject()
{

	auto position = transform_component_->GetPosition();

	if (InputManager::GetInstance().GetKeyPress(VK_UP))
	{
		transform_component_->SetPosition(position.x, position.y + 1);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_DOWN))
	{
		transform_component_->SetPosition(position.x, position.y - 1);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_LEFT))
	{
		transform_component_->SetPosition(position.x - 1, position.y);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_RIGHT))
	{
		transform_component_->SetPosition(position.x + 1, position.y);
	}

}
