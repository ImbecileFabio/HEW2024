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

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager, "Tile")
{
	this->InitGameObject();
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
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Tile::InitGameObject(void)
{
	transform_component_->SetPosition(0, -127);
	transform_component_->SetScale(512, 64);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"tile_01.png");

	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	collider_event_component_->AddEvent([this](GameObject* _other)
		{
			this->OnCollisionEnter(_other);
		});
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
		std::cout << std::format("Tile -> Robot -> OnCollisionEnter\n");
		break;
	case GameObject::TypeID::Lift:
		std::cout << std::format("Tile -> Lift -> OnCollisionEnter\n");
		break;
	default:
		break;
	}
}
