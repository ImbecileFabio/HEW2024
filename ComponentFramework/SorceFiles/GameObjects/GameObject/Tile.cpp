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
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Tile�� -> Constructor\n");


	this->InitGameObject();

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
// ����������
//--------------------------------------------------
void Tile::InitGameObject(void)
{
	transform_component_->SetPosition(0, -127);
	transform_component_->SetScale(512, 64);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"tile_01.png");
	sprite_component_->SetObjectName("Tile");


	collider_component_ = new BoxColliderComponent(this);
}
 
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Tile::UpdateGameObject(void)
{

}