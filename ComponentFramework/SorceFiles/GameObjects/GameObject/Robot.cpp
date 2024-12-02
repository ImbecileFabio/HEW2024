//==================================================
// [Robot.cpp] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイルの処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Robot.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("＜Robot＞ -> Constructor\n");
	this->InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Robot::~Robot(void)
{
	std::cout << std::format("＜Robot＞ -> Destructor\n");
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -100);
	transform_component_->SetScale(50, 50);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/icon.png");
	sprite_component_->SetObjectName("Robot");


	collider_component_ = new BoxColliderComponent(this);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

}