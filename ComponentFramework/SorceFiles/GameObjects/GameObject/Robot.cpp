//==================================================
// [Robot.cpp] ロボットオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの処理を定義
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
#include "../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
{
	this->InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Robot::~Robot(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete velocity_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -25);
	transform_component_->SetScale(150, 150);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/robot_still_01.png");

	collider_component_ = new BoxColliderComponent(this);	// 当たり判定

	velocity_component_ = new VelocityComponent(this);	// 速度
	velocity_component_->SetUseGravity(false);


}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{
	// 移動処理
	if (input.GetKeyPress(VK_D))
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3( 0.1f, 0.0f, 0.0f));
	}
	else if (input.GetKeyPress(VK_A))
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3(-0.1f, 0.0f, 0.0f));
	}
	else
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	}

	

}