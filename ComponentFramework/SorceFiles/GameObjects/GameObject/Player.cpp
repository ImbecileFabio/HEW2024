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
#include "../../GameProcess.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Player::Player(GameManager* _gameManager)
	:GameObject(_gameManager, "Player")
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this,"piyo");
	animation_component_ = new AnimationComponent(this, sprite_component_);

	this->InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Player::~Player(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Player::InitGameObject(void)
{


}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Player::UpdateGameObject(void)
{
	// 入力処理
	InputManager& input = InputManager::GetInstance();

	// マウスクリックで移動
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}
	// 右クリックするとでかくなる！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	if (input.GetMouseButtonTrigger(1)) {
		transform_component_->SetScale(transform_component_->GetScale() *= {1.1f, 1.1f, 1.0f});
	}

}
