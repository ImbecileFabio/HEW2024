//==================================================
// [Player.cpp] プレイヤーオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーの処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Player.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("{}\n", "＜Player＞ -> Constructor");

	// スプライトコンポーネント
	sprite_component_= new SpriteComponent(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("Player");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << std::format("{}\n", "＜Player＞ -> Destructor");
	// ここでコンポーネントを削除
	delete sprite_component_;
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Player::UpdateGameObject(void)
{

}
