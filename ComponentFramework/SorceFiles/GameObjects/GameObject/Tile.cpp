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

#include "../Component/RenderComponent/DebugColliderDrawComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager, "Tile")
{
	sprite_component_ = new SpriteComponent(this, "tile_center");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	// �f�o�b�O
	debug_collider_draw_component_ = new DebugColliderDrawComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&Tile::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	InitGameObject();
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

	delete debug_collider_draw_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Tile::InitGameObject(void)
{
	
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
