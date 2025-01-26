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
#include "Robot.h"

#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/GimmickComponent/LiftComponent.h"
#include "../Component/GimmickComponent/LiftInteractionComponent.h"
#include "Gimmick/Group/LiftGroup.h"

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


//--------------------------------------------------
// @brief リフトに任意のオブジェクトが当たった時の処理
//--------------------------------------------------
void Lift::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		if (auto robot = dynamic_cast<Robot*>(_other))
		{
			if (auto interaction = robot->GetComponent<LiftInteractionComponent>())
			{
				// ロボットにリフトをセット
				interaction->SetLift(this);
			}
		}
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