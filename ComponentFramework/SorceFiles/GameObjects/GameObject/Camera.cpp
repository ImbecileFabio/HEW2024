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
	std::cout << std::format("{}", "��Camera�� -> new\n");

	// �J�����R���|�[�l���g
	camera_component_ = new CameraComponent(this, 0);
	
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Camera::~Camera()
{
	std::cout << std::format("{}", "��Camera�� -> delete\n");
	// �R���|�[�l���g�̍폜
	delete camera_component_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Camera::UpdateGameObject()
{

}
