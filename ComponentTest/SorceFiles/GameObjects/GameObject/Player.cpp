//==================================================
// Player.cpp] プレイヤーゲームオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーゲームオブジェクトの定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "Player.h"
//#include "../Component/RenderConponent/SpriteComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(GameManager* gameManage)
	:GameObject(gameManage)
{
	std::cout << "[プレイヤーゲームオブジェクト] -> 作成\n";

	//sprite_ = new SpriteComponent(this);
	//sprite_->SetObjectName("プレイヤーオブジェクト");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)
{
	std::cout << "[プレイヤーオブジェクト] -> 破棄\n";
}

//--------------------------------------------------
// overrideで自分自身を更新
//--------------------------------------------------
void Player::UpdateGameObject(float deltaTime)
{
	std::cout << "[プレイヤーゲームオブジェクト] -> 更新\n";
}
//==================================================
//				End of FIle
//==================================================
