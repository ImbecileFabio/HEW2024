//==================================================
// [Player.cpp] プレイヤーオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーの処理を定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "Player.h"
#include "../../GameManager.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(std::shared_ptr<GameManager> _gameManager)
	:GameObject(_gameManager)
{
	std::cout << "＜プレイヤー＞ -> 生成\n";
	
	sprite_component_ = std::make_shared<SpriteComponent>(this, "Asset/Texture/icon.png");
	sprite_component_->SetObjectName("プレイヤー");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << "＜プレイヤーオブジェクト＞ -> 破棄\n";
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Player::UpdateGameObject(void)
{

}
