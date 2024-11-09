//==================================================
// [Player.cpp] プレイヤーオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーの処理を定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "Player.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(class GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << "＜プレイヤー＞ -> 生成\n";
	
	sprite_component_ = new SpriteComponent(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("プレイヤー");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << "＜プレイヤー＞ -> 破棄\n";

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	std::cout << "＜プレイヤー＞ -> 更新\n";

}
