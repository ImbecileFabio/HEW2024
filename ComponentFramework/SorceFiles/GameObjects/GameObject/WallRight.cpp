//==================================================
// [WallRight.cpp] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイルの処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "WallRight.h"
#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/PushOutComponent.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
WallRight::WallRight(GameManager* _gameManager)
	:GameObject(_gameManager, "WallRight")
{
	sprite_component_ = new SpriteComponent(this, "wall_right", 80);
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&WallRight::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	sprite_component_->SetFlip(true, false);

	InitGameObject();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
WallRight::~WallRight(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;

}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void WallRight::InitGameObject(void)
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void WallRight::UpdateGameObject(void)
{

}

void WallRight::OnCollisionEnter(GameObject* _other)
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
