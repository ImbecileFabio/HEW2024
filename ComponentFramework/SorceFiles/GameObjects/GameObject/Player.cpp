//==================================================
// [Player.cpp] �v���C���[�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include "../../StdAfx.h"
#include "Player.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Player::Player(class GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << "���v���C���[�� -> ����\n";
	
	sprite_component_ = new SpriteComponent(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("�v���C���[");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << "���v���C���[�� -> �j��\n";

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	std::cout << "���v���C���[�� -> �X�V\n";

}
