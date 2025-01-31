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
#include "../../AudioManager.h"
#include "Lift.h"
#include "Gimmick/Smoke.h"
#include "Gimmick/SmokePipe.h"

#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/GravityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"
#include "../Component/GimmickComponent/SmokeComponent.h"
#include "../Component/GimmickComponent/LiftInteractionComponent.h"
#include "../Component/GimmickComponent/SmokeInteractionComponent.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
	, robot_state_(RobotState::Move)
{
	sprite_component_ = new SpriteComponent(this, "robot_walk", 50);	// スプライト
	animation_component_ = new AnimationComponent(this, sprite_component_);	// アニメーション
	velocity_component_ = new VelocityComponent(this, 5);	// 速度
	gravity_component_ = new GravityComponent(this, 6);	// 重力
	collider_component_ = new BoxColliderComponent(this, 10);	// 当たり判定
	collider_event_component_ = new ColliderEventComponent(this, 11);	// 当たり判定イベント
	robot_move_component_ = new RobotMoveComponent(this, 3);	// ロボット移動
	push_out_component_ = new PushOutComponent(this, 15);	// 押し出し
	lift_interaction_component_ = new LiftInteractionComponent(this, 20);	// リフトとのやり取り

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
	transform_component_->SetSize(TILE_SIZE_X * 2.0f, TILE_SIZE_Y * 2.0f);
	collider_component_->SetSize(transform_component_->GetSize().x * 0.7f, transform_component_->GetSize().y * 0.95f);
	collider_component_->SetLayer(ColliderBaseComponent::Robot);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
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




	// stateによって処理を変える
	switch (robot_state_)
	{
	case RobotState::Idle:	// 待機状態
	{
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
		{
			if (robot_state_ != RobotState::Move)
			{
				robot_state_ = RobotState::Move;
				sprite_component_->SetTexture("robot_walk");
			}
		}
		break;
	}
	case RobotState::Move:	// 移動状態
	{
		// 落ちていたら
		if (!gravity_component_->CheckGroundCollision()) {
			if (robot_state_ != RobotState::Fall)
			{
				robot_state_ = RobotState::Fall;
				sprite_component_->SetTexture("robot_drop");
			}
		}


		// サウンドを繰り返す処理
		if (!AudioManager::GetInstance()->GetPlayingState(SoundLabel_RobotMoveSE))
			AudioManager::GetInstance()->Play(SoundLabel_RobotMoveSE);
		break;
	}
	case RobotState::Fall:	// 落下状態
	{
		// 地面についたら
		if (gravity_component_->CheckGroundCollision()) {
			// 移動状態に遷移
			if (robot_state_ != RobotState::Move)
			{
				robot_state_ = RobotState::Move;
				sprite_component_->SetTexture("robot_walk");
			}
			AudioManager::GetInstance()->Play(SoundLabel_RobotLandingSE);
		}
		break;
	}
	case RobotState::OnLift:	// リフトに乗っている状態
	{
		if (lift_interaction_component_->GetLift() == nullptr)
		{
			robot_state_ = RobotState::Move;
			sprite_component_->SetTexture("robot_walk");
		}

		break;
	}
	}


	// ロボットの動きを切り替える
	robot_move_component_->SetState(static_cast<RobotMoveComponent::RobotMoveState>(robot_state_));

	// 進行方向に合わせて画像を反転する
	if (velocity_component_->GetVelocity().x > 0) {	// 右向き
		sprite_component_->SetFlip(true, false);
	}
	else if (velocity_component_->GetVelocity().x < 0) {	// 左向き
		sprite_component_->SetFlip(false, false);
	}

}


void Robot::OnCollisionEnter(GameObject* _other)
{

	if (state_ == State::Paused) return;


	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}
		break;
	}
	case GameObject::TypeID::Lift:
	{
		auto lift = dynamic_cast<Lift*>(_other);

		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}

		// リフトが動いていないなら
		if (lift->GetLiftState() == Lift::LiftState::Stop) {
			robot_state_ = RobotState::Move;
			sprite_component_->SetTexture("robot_walk");
			return;
		}

		// まだOnLiftではなければ
		if(robot_state_ != RobotState::OnLift)
		{
			if (lift_interaction_component_->IsTouchingLiftCenter(lift))
			{
				lift_interaction_component_->SetLift(lift);
				robot_state_ = RobotState::OnLift;
				lift->SetLiftState(Lift::LiftState::Move);
				sprite_component_->SetTexture("robot_still");
			}
		}




		break;
	}
	case GameObject::TypeID::WeakFloor:
	{
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}
		break;
	}
	case GameObject::TypeID::Smoke:
	{
		auto pos = transform_component_->GetPosition();
		auto vel = velocity_component_->GetVelocity();

		auto smoke = dynamic_cast<Smoke*>(_other);
		auto smokepipe = dynamic_cast<SmokePipe*>(smoke->GetOwnerObj());

		if (smokepipe->GetBrakeFlg())
		{
			if (pos.y <= smoke->GetTransformComponent()->GetPosition().y + smoke->GetTransformComponent()->GetSize().y) {
				transform_component_->SetPosition({
					pos.x,
					pos.y + 10.0f,
					pos.z
					});
			}
		}
		break;
	}
	case GameObject::TypeID::SteePillarFloor:
	{
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