//==================================================
// [WallLeft.cpp] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C���̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "WallLeft.h"
#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/PushOutComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
WallLeft::WallLeft(GameManager* _gameManager)
	:GameObject(_gameManager, "WallLeft")
{
	sprite_component_ = new SpriteComponent(this, "wall_left");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&WallLeft::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);


	InitGameObject();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
WallLeft::~WallLeft(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;

}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void WallLeft::InitGameObject(void)
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void WallLeft::UpdateGameObject(void)
{

}

void WallLeft::OnCollisionEnter(GameObject* _other)
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
