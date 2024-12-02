//==================================================
// [Robot.cpp] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C���̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Robot.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Robot�� -> Constructor\n");
	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Robot::~Robot(void)
{
	std::cout << std::format("��Robot�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -100);
	transform_component_->SetScale(50, 50);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/icon.png");
	sprite_component_->SetObjectName("Robot");


	collider_component_ = new BoxColliderComponent(this);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

}