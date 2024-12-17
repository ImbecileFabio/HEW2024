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
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/PushOutComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager, "Tile")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"tile_01.png");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&Tile::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(3, f);this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Tile::~Tile(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Tile::InitGameObject(void)
{
	transform_component_->SetScale(512, 64);
	transform_component_->SetPosition(0, -127);
	transform_component_->SetScale(512, 64);


}
 
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Tile::UpdateGameObject(void)
{

}

void Tile::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		break;
	case GameObject::TypeID::Lift:
		break;
	default:
		break;
	}
}
