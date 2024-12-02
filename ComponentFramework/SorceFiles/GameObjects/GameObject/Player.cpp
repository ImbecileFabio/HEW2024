//==================================================
// [Player.cpp] �v���C���[�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Player.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Player::Player(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Player�� -> Constructor\n");

	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << std::format("��Player�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete velocity_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Player::InitGameObject(void)
{
	transform_component_->SetPosition(0, 0);
	transform_component_->SetScale(50, 50);

	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"icon.png");
	sprite_component_->SetObjectName("Player");

	// ���x�R���|�[�l���g
	velocity_component_ = new VelocityComponent(this);
	velocity_component_->SetVelocity(Vector3(0, 10, 0));


	collider_component_ = new BoxColliderComponent(this);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{

}
