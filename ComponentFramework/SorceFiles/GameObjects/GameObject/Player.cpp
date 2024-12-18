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
	:GameObject(_gameManager, "Playaer")
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"icon.png");
	// ���x�R���|�[�l���g
	velocity_component_ = new VelocityComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
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
	transform_component_->SetScale(50, 50);

	velocity_component_->SetVelocity(Vector3(0, 10, 0));

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{

}
