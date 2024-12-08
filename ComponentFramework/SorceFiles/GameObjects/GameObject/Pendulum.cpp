//==================================================
// [Pendulum.cpp] 振り子オブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：振り子の処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Pendulum.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager, "Pendulum")
{
	this->InitGameObject();

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete pendulum_movement_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");

	// 振り子コンポーネント
	pendulum_movement_component_ = new PendulumMovementComponent(this);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
