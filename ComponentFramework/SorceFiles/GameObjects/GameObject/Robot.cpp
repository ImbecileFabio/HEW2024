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

#include "../../GameProcess.h"	// windowサイズとるためだけ
#include "../../GameManager.h"
#include "../Component.h"

#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"

// デバッグ用コンポーネント
#include "../Component/RenderComponent/DebugCollisionDrawComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/robot_still_01.png");
	collider_component_ = new BoxColliderComponent(this);	// 当たり判定
	collider_event_component_ = new ColliderEventComponent(this);	// 当たり判定イベント
	velocity_component_ = new VelocityComponent(this);	// 速度
	//robot_move_component_ = new RobotMoveComponent(this);	// ロボット移動
	push_out_component_ = new PushOutComponent(this);	// 押し出し

	auto f = std::function<void(GameObject*)>(std::bind(&Robot::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);


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
	delete collider_event_component_;
	delete velocity_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -25);
	transform_component_->SetScale(150, 150);

	velocity_component_->SetUseGravity(true);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

	// 入力処理
	InputManager& input = InputManager::GetInstance();

	// デバッグ用、ロボを操作できる
	// 移動処理
	if (input.GetKeyPress(VK_A))
	{
		velocity_component_->SetVelocity(Vector3(-10, 0, 0));
	}
	else if (input.GetKeyPress(VK_D))
	{
		velocity_component_->SetVelocity(Vector3(10, 0, 0));
	}
	else if (input.GetButtonPress(VK_W))
	{
		velocity_component_->SetVelocity(Vector3(0, 10, 0));
	}
	else if (input.GetButtonPress(VK_S))
	{
		velocity_component_->SetVelocity(Vector3(0, -10, 0));
	}
	else
	{
		velocity_component_->SetVelocity(Vector3(0, 0, 0));
	}

	// マウスクリックで移動
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			  static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}


	// 重力を適用、
	velocity_component_->SetUseGravity(true);

}

void Robot::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		std::cout << std::format("Robot -> Tile -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}
		break;
	}

	case GameObject::TypeID::Lift:
	{
		std::cout << std::format("Robot -> Lift -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}
		break;
	}
	default:
		break;
	}
}
