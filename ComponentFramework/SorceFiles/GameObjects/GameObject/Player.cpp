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
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Player::Player(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Player�� -> Constructor\n");

	// �X�v���C�g�R���|�[�l���g
	sprite_component_= new SpriteComponent(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("Player");

	transform_component_->SetScale(100, 100);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << std::format("��Player�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
}
