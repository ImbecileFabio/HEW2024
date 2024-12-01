//==================================================
// [Tile.cpp] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C���̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Tile.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Tile�� -> Constructor\n");

	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/HEW���f��/TestBlock4.png");
	sprite_component_->SetObjectName("Tile");

	transform_component_->SetPosition(0,-100);
	transform_component_->SetScale(50, 50);

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Tile::~Tile(void)
{
	std::cout << std::format("��Tile�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Tile::UpdateGameObject(void)
{

}
