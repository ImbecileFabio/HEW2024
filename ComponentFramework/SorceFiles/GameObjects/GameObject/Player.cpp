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
#include "../../GameProcess.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Player::Player(GameManager* _gameManager)
	:GameObject(_gameManager, "Player")
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this,"piyo");
	animation_component_ = new AnimationComponent(this, sprite_component_);

	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Player::~Player(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Player::InitGameObject(void)
{


}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	// ���͏���
	InputManager& input = InputManager::GetInstance();

	// �}�E�X�N���b�N�ňړ�
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}
	// �E�N���b�N����Ƃł����Ȃ�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
	if (input.GetMouseButtonTrigger(1)) {
		transform_component_->SetScale(transform_component_->GetScale() *= {1.1f, 1.1f, 1.0f});
	}

}
