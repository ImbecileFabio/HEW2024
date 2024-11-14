//==================================================
// [Player.cpp] �v���C���[�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include "../../StdAfx.h"
#include "Player.h"
#include "../../GameManager.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Player::Player(std::shared_ptr<GameManager> _gameManager)
	:GameObject(_gameManager)
{
	std::cout << "���v���C���[�� -> ����\n";
	
	sprite_component_ = std::make_shared<SpriteComponent>(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("�v���C���[");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << "���v���C���[�I�u�W�F�N�g�� -> �j��\n";
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{

}
