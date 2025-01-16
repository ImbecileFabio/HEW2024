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
#include "../../TileMapManager.h"
#include "Lift.h"

#include "../Component.h"

#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/GravityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
	, robot_state_(RobotState::Idle)
{
	sprite_component_ = new SpriteComponent(this, "robot_still");
	velocity_component_ = new VelocityComponent(this);	// 速度
	gravity_component_ = new GravityComponent(this);	// 重力
	collider_component_ = new BoxColliderComponent(this);	// 当たり判定
	collider_event_component_ = new ColliderEventComponent(this);	// 当たり判定イベント
	robot_move_component_ = new RobotMoveComponent(this);	// ロボット移動
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
	delete gravity_component_;
	delete robot_move_component_;
	delete push_out_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetSize(TILE_SIZE_X * 1.5, TILE_SIZE_Y * 1.5);
	collider_component_->SetSize(transform_component_->GetSize().x * 0.7, transform_component_->GetSize().y * 0.95);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

	// 入力処理
	InputManager& input = InputManager::GetInstance();

	//// デバッグ用、ロボを操作できる
	//// 移動処理
	//if (input.GetKeyPress(VK_A))
	//{
	//	velocity_component_->SetVelocity(Vector3(-10, 0, 0));
	//}
	//else if (input.GetKeyPress(VK_D))
	//{
	//	velocity_component_->SetVelocity(Vector3(10, 0, 0));
	//}
	//else
	//{
	//	velocity_component_->SetVelocity(Vector3(0, 0, 0));
	//}

	// マウスクリックで移動
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			  static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}


	switch (robot_state_)
	{
	case RobotState::Idle:	// 待機状態
	{
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN)) {
			robot_state_ = RobotState::Move;
		}
		break;
	}
	case RobotState::Move:	// 移動状態
	{
		if (!gravity_component_->GetIsGround()) {
			robot_state_ = RobotState::Fall;
		}
		break;
	}
	case RobotState::Fall:	// 落下状態
	{
		if (gravity_component_->GetIsGround()) {
			robot_state_ = RobotState::Move;
		}
		break;
	}
	case RobotState::OnLift:	// リフトに乗っている状態
	{

		break;
	}
	}

	// ロボットの動きを切り替える
	robot_move_component_->SetState(static_cast<RobotMoveComponent::RobotMoveState>(robot_state_));

}

void Robot::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		//std::cout << std::format("Robot -> Tile -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}
		break;
	}

	case GameObject::TypeID::Lift:
	{
		//std::cout << std::format("Robot -> Lift -> OnCollisionEnter\n");
		
		auto lift = dynamic_cast<Lift*>(_other);

		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}

		// リフトが動いているなら
		if (lift->GetLiftState() == Lift::LiftState::Move)
		{
			robot_state_ = Robot::RobotState::OnLift;
		}
		else {
			robot_state_ = Robot::RobotState::Move;
		}

		velocity_component_->SetVelocity(lift->GetComponent<VelocityComponent>()->GetVelocity());
		break;
	}
	default:
		break;
	}
}
