//==================================================
// [Player.h] �v���C���[�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����̏������`
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

	sprite_ = new SpriteComponent(this, L"../../../Asset/Texture/icon.png");
	sprite_->SetObjectName("�v���C���[");

	transform_ = new TransformComponent(this);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)

{
	// �����ŃR���|�[�l���g�̉���s��...?
	std::cout << "���v���C���[�� -> �j��\n";
	delete sprite_;
	delete transform_;
}

//--------------------------------------------------
// override�Ŏ������g���X�V
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	std::cout << "���v���C���[�� -> �X�V\n";
}

//==================================================
//				End of FIle
//==================================================