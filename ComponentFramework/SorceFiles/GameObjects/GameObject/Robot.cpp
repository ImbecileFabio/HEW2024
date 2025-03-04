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

#include "Effect//Effect.h"


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

	audio_manager_ = std::make_unique<AudioManager>();

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

#ifdef _DEBUG || DEBUG)	// デバッグ用
	//// マウスクリックで移動
	//if (input.GetMouseButtonPress(0)) {
	//	auto mousePos = input.GetMousePosition();
	//	transform_component_->SetPosition(
	//		static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
	//		-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	//}
#endif



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
		if (!audio_manager_->GetPlayingState(SoundLabel_RobotMoveSE))
			audio_manager_->Play(SoundLabel_RobotMoveSE);
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
			audio_manager_->Play(SoundLabel_RobotLandingSE);
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
	case RobotState::OnSmoke:
	{
		break;
	}
	}

	// 常に地面判定を行い、重力の有効/無効を切り替える
	if (gravity_component_)
	{
		// リフトに乗っている時は重力を無効化、それ以外は地面判定に応じて重力を適用
		if (robot_state_ == RobotState::OnLift)
		{
			gravity_component_->SetUseGravityFlg(false);
		}
		else
		{
			gravity_component_->SetUseGravityFlg(!gravity_component_->CheckGroundCollision());
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

	std::cout << "x : " << velocity_component_->GetVelocity().x << std::endl;
	std::cout << "y : " << velocity_component_->GetVelocity().y << std::endl;

}



void Robot::OnCollisionEnter(GameObject* _other)
{


	if (state_ == State::Paused) return;


	if (gravity_component_->CheckGroundCollision()) {
		gravity_component_->SetUseGravityFlg(true);
	}


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
		if (robot_state_ == RobotState::OnLift) { return; }	// OnLift状態なら処理しない



		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// 押し出し処理
		}


		auto lift = dynamic_cast<Lift*>(_other);

		// リフトが動いていないなら
		if (lift->GetLiftState() == Lift::LiftState::Stop) {
			robot_state_ = RobotState::Move;
			sprite_component_->SetTexture("robot_walk");
			lift_interaction_component_->SetLift(nullptr);

			if (gravity_component_) {
				gravity_component_->SetUseGravityFlg(true);
			}
			return;
		}

		if (lift_interaction_component_->IsTouchingLiftCenter(lift))
		{
			lift_interaction_component_->SetLift(lift);
			robot_state_ = RobotState::OnLift;
			lift->SetLiftState(Lift::LiftState::Move);
			sprite_component_->SetTexture("robot_still");
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

		auto robotPos = transform_component_->GetPosition();
		auto robotHitbox = collider_component_->GetWorldHitBox();
		auto smoke = dynamic_cast<Smoke*>(_other);
		auto smokepipe = dynamic_cast<SmokePipe*>(smoke->GetOwnerObj());
		auto smokeHitbox = smoke->GetComponent<BoxColliderComponent>()->GetWorldHitBox();



		// 排煙管が壊れているなら
		if (smokepipe->GetBreakFlg())
		{
			// 重力を無効化
			gravity_component_->SetUseGravityFlg(false);

			if(robotHitbox.min_.y <= smokeHitbox.max_.y)
			{
				// 自身を上に押し上げる
				float up = 10.0f;
				transform_component_->SetPosition(robotPos.x, robotPos.y + up, robotPos.z);
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
	{
		break;

	}
	}
}