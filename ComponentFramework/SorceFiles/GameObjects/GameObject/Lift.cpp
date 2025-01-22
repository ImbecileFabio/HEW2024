//==================================================
// [Lift.cpp] リフトファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフト関係のState管理などを行うことにしてます
//==================================================
/*----- インクルード -----*/
#include <algorithm>
#include "Lift.h"
#include "Pendulum.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/GimmickComponent/LiftComponent.h"
#include "Gimmick/LiftGroup.h"

Lift::Lift(GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, lift_state_(Lift::LiftState::Stop)
	, move_state_(MoveState::length)
	, turn_count_(0)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);


	// イベント追加処理
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
	this->InitGameObject();
}
//--------------------------------------------------
// @brief コンストラクタ
// @param _moveState 移動状態
// @param _endPos 切り返し地点
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(GameManager* _gameManager, MoveState _moveState, Vector3 _startPos, Vector3 _endPos, Pendulum* _pendulum)
	:GameObject(_gameManager, "Lift")
	, pendulum_(_pendulum)
	, turn_count_(0)
	, lift_state_(Lift::LiftState::Stop)
	, move_state_(_moveState)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	lift_component_ = new LiftComponent(this, static_cast<LiftComponent::LiftComMoveState>(move_state_), _startPos, _endPos, pendulum_);
	// イベント追加処理
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Lift::~Lift()
{
	delete collider_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	lift_state_ = Lift::LiftState::Stop;
	turn_count_ = 0;
}


//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;

	// 振り子が動いているかどうか
	auto pendulumMoveFlg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();

	switch (lift_state_) 
	{
	case Lift::LiftState::Stop:
	{
		// カウントが0になったら次の状態に遷移
		if (turn_count_  <= 0) {
			if (pendulumMoveFlg)
			{
				lift_state_ = Lift::LiftState::Move;
				turn_count_ = 180;
			}
		}
		else {
			--turn_count_;
		}
		break;
	}
	case Lift::LiftState::Move:
	{
		if (!pendulumMoveFlg)
		{
			lift_state_ = Lift::LiftState::Stop;
			turn_count_ = 0;	// 移動中に止まったら次動くときはすぐ動かせるように
		}

		// リフトの移動距離が最大距離を超えたら切り返す
		if (lift_component_->CheckTraveledDistance()) {
			lift_state_ = Lift::LiftState::Stop;
		}
		break;
	}
	}
	// stateをセット
	lift_component_->SetLiftComState(static_cast<LiftComponent::LiftComState>(lift_state_));
	// グループのタイルを揃える処理
	lift_group_->UpdateLiftTilePositions();
}

// まだテスト段階なのでコメントアウトをしておきます, by arima
////--------------------------------------------------
//// @brief 更新処理
////--------------------------------------------------
//void Lift::UpdateGameObject(void)
//{
//	if (!pendulum_) return;
//
//	// 切り替え時一定時間停止する
//	switch (lift_state_)
//	{
//	case Lift::LiftState::Stop:
//	{
//		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//
//		if (turn_count_ >= 180) {
//			if (pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement())
//			{
//				lift_state_ = Lift::LiftState::Move;
//				turn_count_ = 0;
//			}
//		}
//		else {
//			++turn_count_;
//		}
//
//		return;
//		break;
//	}
//	case Lift::LiftState::Move:
//	{
//		if (!pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement())
//		{
//			lift_state_ = Lift::LiftState::Stop;
//			velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//			turn_count_ = 180;
//			return;
//		}
//
//		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
//		switch (moveState_)
//		{
//		case Lift::MoveState::length:	// 縦移動
//			if (!switchFg_)
//			{
//				// 上に移動
//				direction_ = { 0.0f, 1.0f };
//				// 移動距離を累積
//				traveledDistance_.y += std::abs(direction_.y) * velocity_component_->GetSpeedRate();
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.y >= maxMoveDistance_)
//				{
//					// 逆方向に移動
//					direction_ = { 0.0f, -1.0f };
//					traveledDistance_.y = 0.0f;
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// 下に移動
//				direction_ = { 0.0f, -1.0f };
//				// 移動距離を累積
//				traveledDistance_.y += std::abs(direction_.y) * velocity_component_->GetSpeedRate();
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.y >= maxMoveDistance_)
//				{
//					// 逆方向に移動
//					direction_ = { 0.0f, 1.0f };
//					traveledDistance_.y = 0.0f;
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::side:		// 横移動
//			if (!switchFg_)
//			{
//				// 右に移動
//				direction_ = { 1.0f, 0.0f };
//				// 移動距離を累積
//				traveledDistance_.x += std::abs(direction_.x) * velocity_component_->GetSpeedRate();
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_)
//				{
//					direction_ = { -1.0f, 0.0f };	// 逆方向に移動
//					traveledDistance_.x = 0.0f;
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// 左に移動
//				direction_ = { -1.0f, 0.0f };
//				// 移動距離を累積
//				traveledDistance_.x += std::abs(direction_.x) * velocity_component_->GetSpeedRate();
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_)
//				{
//					direction_ = { 1.0f, 0.0f };	// 逆方向に移動
//					traveledDistance_.x = 0.0f;
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonalRight:	// 斜め移動（右）
//			if (!switchFg_)
//			{
//				// 右上に移動
//				direction_ = { 1.0f, 1.0f };
//				// 移動距離を累積
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { -1.0f, -1.0f };
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// 左下に移動
//				direction_ = { -1.0f, -1.0f };
//				// 移動距離を累積
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { 1.0f, 1.0f };
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonalLeft:	// 斜め移動（左）
//			if (!switchFg_)
//			{
//				// 左上に移動
//				direction_ = { -1.0f, 1.0f };
//				// 移動距離を累積
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { 1.0f, -1.0f };
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// 右下に移動
//				direction_ = { 1.0f, -1.0f };
//				// 移動距離を累積
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// 移動距離が最大移動距離を超えたら
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { -1.0f, 1.0f };
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		default:
//			break;
//		}
//		// リフトの座標を支点として渡し続ける
//		velocity_component_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
//		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
//	}
//	}
//}

//--------------------------------------------------
// @brief リフトに任意のオブジェクトが当たった時の処理
//--------------------------------------------------
void Lift::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		break;
	case GameObject::TypeID::Tile:
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// @brief リフトに連動させたい振り子を設定
//--------------------------------------------------
void Lift::SetPendulum(Pendulum* _pendulum)
{
	pendulum_ = _pendulum;
	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
}
//--------------------------------------------------
// @brief リフトの移動状態を設定
//--------------------------------------------------
void Lift::SetMoveState(Lift::MoveState _state)
{
	move_state_ = _state;
}