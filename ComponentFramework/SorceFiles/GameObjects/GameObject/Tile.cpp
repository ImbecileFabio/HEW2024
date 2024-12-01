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
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Tile::Tile(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("＜Tile＞ -> Constructor\n");

	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/HEW仮素材/TestBlock4.png");
	sprite_component_->SetObjectName("Tile");

	transform_component_->SetPosition(0,-100);
	transform_component_->SetScale(50, 50);

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
// 更新処理
//--------------------------------------------------
void Tile::UpdateGameObject(void)
{

}
