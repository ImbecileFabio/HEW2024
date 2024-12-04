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
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("＜Tile＞ -> Constructor\n");


	this->InitGameObject();

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Tile::~Tile(void)
{
	std::cout << std::format("＜Tile＞ -> Destructor\n");
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
}

//--------------------------------------------------
// 初期化処理
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
// 更新処理
//--------------------------------------------------
void Tile::UpdateGameObject(void)
{

}