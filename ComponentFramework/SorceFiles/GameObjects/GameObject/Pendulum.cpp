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
#include "../Component/PendulumComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("＜Pendulum＞ -> Constructor\n");
	this->InitGameObject();

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	std::cout << std::format("＜Pendulum＞ -> Destructor\n");
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete pendulum_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"HEW仮素材/Ball.png");
	sprite_component_->SetObjectName("Pendulum");

	// 振り子コンポーネント
	pendulum_component_ = new PendulumComponent(this);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
