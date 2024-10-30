//==================================================
// [Player.h] プレイヤーオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラの処理を定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "Player.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(class GameManager* gameManager)
	:GameObject(gameManager)
{
	std::cout << "＜プレイヤー＞ -> 生成\n";

	sprite_ = new SpriteComponent(this);
	sprite_->SetObjectName("プレイヤー");

	transform_ = new TransformComponent(this);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)

{
	// ここでコンポーネントの解放行う...?
	std::cout << "＜プレイヤー＞ -> 破棄\n";
	delete sprite_;
	delete transform_;
}

//--------------------------------------------------
// overrideで自分自身を更新
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	std::cout << "＜プレイヤー＞ -> 更新\n";
}

//==================================================
//				End of FIle
//==================================================