//==================================================
// [Wall.cpp] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C���̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Wall.h"
#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/PushOutComponent.h"

#include "../Component/RenderComponent/DebugColliderDrawComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Wall::Wall(GameManager* _gameManager)
	:GameObject(_gameManager, "Wall")
{
	sprite_component_ = new SpriteComponent(this, "tile_wall");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&Wall::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	auto offsetPos = sprite_component_->GetTexture()->GetOffsetPos();
	collider_component_->SetOffset({ offsetPos.x, offsetPos.y , 0.0f});

	new DebugColliderDrawComponent(this);

	InitGameObject();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Wall::~Wall(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;

}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Wall::InitGameObject(void)
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Wall::UpdateGameObject(void)
{

}

void Wall::OnCollisionEnter(GameObject* _other)
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
