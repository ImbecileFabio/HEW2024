//==================================================
// [Lift.cpp] リフトファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトオブジェクト
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
#include "../Component/ChildrenComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
// @param _maxPos 正方向の最大座標
// @param _minPos 負方向の最大座標
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(GameManager* _gameManager)
	: GameObject(_gameManager, "Lift")
	, maxPos_(DirectX::SimpleMath::Vector3::Zero)
	, minPos_(DirectX::SimpleMath::Vector3::Zero)
	, direction_(0.0f, 0.0f)
	, moveState_(Lift::MoveState::length)
	, switchFg_(false)
{
	sprite_component_		  = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_  = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_		  = new VelocityComponent(this);
	velocity_component_->SetSpeedRate(2.0f);
	// イベント追加処理
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
Lift::Lift(Lift::MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	: GameObject(_gameManager, "Lift")
	, maxPos_(_maxPos)
	, minPos_(_minPos)
	, direction_(0.0f, 0.0f)
	, moveState_(_moveState)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	velocity_component_->SetSpeedRate(2.0f);
	// リフトの座標で振り子を生成
	DirectX::SimpleMath::Vector3 pos = GetTransformComponent()->GetPosition();

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
	delete collider_base_component_;
	delete collider_event_component_;
	delete velocity_component_;
	delete sprite_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	transform_component_->SetSize(200.0f, 200.0f);
	velocity_component_->SetUseGravity(false);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;	// 振り子が設定されていない場合は処理を行わない
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();

	// 振り子が動いていたらリフトを動かす
	if (moveFg)
	{	// リフトの座標と取得
		DirectX::SimpleMath::Vector3 liftPos = GetTransformComponent()->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// 縦移動
			if (!switchFg_)
			{
				direction_ = Vector2(0.0f, 1.0f);
				if (liftPos.y >= maxPos_.y)
				{
					direction_ = Vector2(0.0f, -1.0f);
					switchFg_ = true;
				}
			}
			else
			{
				direction_ = Vector2(0.0f, -1.0f);
				if (liftPos.y <= minPos_.y)
				{
					direction_ = Vector2(0.0f, 1.0f);
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// 横移動
			if (!switchFg_)
			{
				direction_ = Vector2(1.0f, 0.0f);
				if (liftPos.x >= maxPos_.x)
				{
					direction_ = Vector2(-1.0f, 0.0f);
					switchFg_ = true;
				}
			}
			else
			{
				direction_ = Vector2(-1.0f, 0.0f);
				if (liftPos.x <= minPos_.x)
				{
					direction_ = Vector2(1.0f, 0.0f);
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonal:	// 斜め移動
			if (!switchFg_)
			{
				direction_ = Vector2(1.0f, 1.0f);
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					direction_ = Vector2(-1.0f, -1.0f);
					switchFg_ = true;
				}
			}
			else {
				direction_ = Vector2(-1.0f, -1.0f);
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
				{
					direction_ = Vector2(1.0f, 1.0f);
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// 最終的な移動
		float speed = velocity_component_->GetSpeedRate();
		velocity_component_->SetVelocity(Vector3(direction_.x * speed, direction_.y * speed, 0.0f));
		// リフトの座標を支点として渡し続ける
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
	}

}
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
// @brief リフトの正方向の最大座標を設定
//--------------------------------------------------
void Lift::SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos)
{
	maxPos_ = _maxPos;
}
//--------------------------------------------------
// @brief リフトの負方向の最大座標を設定
//--------------------------------------------------
void Lift::SetMinPos(DirectX::SimpleMath::Vector3 _minPos)
{
	minPos_ = _minPos;
}
//--------------------------------------------------
// @brief リフトと連動させる振り子を設定
// @param _pendulum 連動させる振り子
//--------------------------------------------------
void Lift::SetPendulum(Pendulum* _pendulum)
{
	pendulum_ = _pendulum;
	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
	transform_component_->SetPosition(fulcrum);
}
//--------------------------------------------------
// @brief リフトの移動状態を設定
//--------------------------------------------------
void Lift::SetMoveState(Lift::MoveState _moveState)
{
	moveState_ = _moveState;
}
