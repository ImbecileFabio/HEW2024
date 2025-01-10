//==================================================
// [Tile.cpp] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイルの処理を定義
//==================================================

/*----- インクルード -----*/
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
// コンストラクタ
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager, "Tile")
{
	sprite_component_ = new SpriteComponent(this, "tile_center");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);

	// デバッグ
	debug_collider_draw_component_ = new DebugColliderDrawComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&Tile::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Tile::~Tile(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;

	delete debug_collider_draw_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Tile::InitGameObject(void)
{
	
}
 
//--------------------------------------------------
// 更新処理
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
