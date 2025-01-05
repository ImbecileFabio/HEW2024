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
Lift::Lift(GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, moveState_(MoveState::length)
	, startPos_(0.0f, 0.0f, 0.0f)
	, traveledDistance_(0.0f, 0.0f)
	, maxMoveDistance_(0.0f)
	, direction_(0.0f, 0.0f)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
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
// @param _moveDistance 最大移動距離
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(MoveState _moveState, float _moveDistance, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, moveState_(_moveState)
	, traveledDistance_(0.0f, 0.0f)
	, maxMoveDistance_(_moveDistance)
	, direction_(0.0f, 0.0f)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this,"lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	// イベント追加処理
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
	// リフトの開始座標を取得
	startPos_ = transform_component_->GetPosition();

	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Lift::~Lift()
{
	delete collider_base_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	velocity_component_->SetUseGravity(false);

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// 縦移動
			if (!switchFg_) 
			{
				// 上に移動
				direction_ = { 0.0f, 1.0f };
				// 移動距離を累積
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.y >= maxMoveDistance_)
				{
					// 逆方向に移動
					direction_ = { 0.0f, -1.0f };
					traveledDistance_.y = 0.0f;
					switchFg_ = true;
				}
			}
			else 
			{
				// 下に移動
				direction_ = { 0.0f, -1.0f };
				// 移動距離を累積
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.y >= maxMoveDistance_) 
				{
					// 逆方向に移動
					direction_ = { 0.0f, 1.0f };
					traveledDistance_.y = 0.0f;
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// 横移動
			if (!switchFg_) 
			{
				// 右に移動
				direction_ = { 1.0f, 0.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_)
				{
					direction_ = { -1.0f, 0.0f };	// 逆方向に移動
					traveledDistance_.x = 0.0f;
					switchFg_ = true;
				}
			}
			else 
			{
				// 左に移動
				direction_ = { -1.0f, 0.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_)
				{
					direction_ = { 1.0f, 0.0f };	// 逆方向に移動
					traveledDistance_.x = 0.0f;
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonalRight:	// 斜め移動（右）
			if (!switchFg_)
			{
				// 右上に移動
				direction_ = { 1.0f, 1.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { -1.0f, -1.0f };
					switchFg_ = true;
				}
			}
			else
			{
				// 左下に移動
				direction_ = { -1.0f, -1.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { 1.0f, 1.0f };
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonalLeft:	// 斜め移動（左）
			if (!switchFg_)
			{
				// 左上に移動
				direction_ = { -1.0f, 1.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { 1.0f, -1.0f };
					switchFg_ = true;
				}
			}
			else
			{
				// 右下に移動
				direction_ = { 1.0f, -1.0f };
				// 移動距離を累積
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// 移動距離が最大移動距離を超えたら
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { -1.0f, 1.0f };
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// リフトの座標を支点として渡し続ける
		velocity_component_->SetVelocity(Vector3(direction_.x , direction_.y, 0.0f));
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
void Lift::SetMoveState(Lift::MoveState _moveState)
{
	moveState_ = _moveState;
}

//Lift::Lift(GameManager* _gameManager)
//	:GameObject(_gameManager, "Lift")
//	, moveState_(MoveState::length)
//	, maxPos_(0.0f, 0.0f, 0.0f)
//	, direction_(0.0f, 0.0f)
//	, minPos_(0.0f, 0.0f, 0.0f)
//	, switchFg_(false)
//{
//	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
//	collider_base_component_ = new BoxColliderComponent(this);
//	collider_event_component_ = new ColliderEventComponent(this);
//	velocity_component_ = new VelocityComponent(this);
//	// イベント追加処理
//	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
//	collider_event_component_->AddEvent(f);
//	this->InitGameObject();
//}
////--------------------------------------------------
//// @brief コンストラクタ
//// @param _maxPos 正方向の最大座標
//// @param _minPos 負方向の最大座標
//// @param _gameManager オブジェクトを所持しているマネージャー
////--------------------------------------------------
//Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
//	:GameObject(_gameManager, "Lift")
//	, moveState_(_moveState)
//	, maxPos_(_maxPos)
//	, direction_(0.0f, 0.0f)
//	, minPos_(_minPos)
//	, switchFg_(false)
//{
//	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
//	collider_base_component_ = new BoxColliderComponent(this);
//	collider_event_component_ = new ColliderEventComponent(this);
//	velocity_component_ = new VelocityComponent(this);
//	// イベント追加処理
//	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
//	collider_event_component_->AddEvent(f);
//
//	this->InitGameObject();
//}
////--------------------------------------------------
//// @brief デストラクタ
////--------------------------------------------------
//Lift::~Lift()
//{
//	delete collider_base_component_;
//	delete collider_event_component_;
//	delete sprite_component_;
//	delete velocity_component_;
//}
////--------------------------------------------------
//// @brief 初期化処理
////--------------------------------------------------
//void Lift::InitGameObject(void)
//{
//	velocity_component_->SetUseGravity(false);
//
//}
////--------------------------------------------------
//// @brief 更新処理
////--------------------------------------------------
//void Lift::UpdateGameObject(void)
//{
//	if (!pendulum_) return;
//	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
//	if (moveFg)
//	{
//		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
//		switch (moveState_)
//		{
//		case Lift::MoveState::length:	// 縦移動
//			if (!switchFg_)
//			{
//				direction_ = { 0.0f, 2.0f };
//				if (liftPos.y >= maxPos_.y)
//				{
//					direction_ = { 0.0f, -2.0f };
//					switchFg_ = true;
//				}
//			}
//			else
//			{
//				direction_ = { 0.0f, -2.0f };
//				if (liftPos.y <= minPos_.y)
//				{
//					direction_ = { 0.0f, 2.0f };
//					switchFg_ = false;
//				}
//			}
//			break;
//		case Lift::MoveState::side:		// 横移動
//			if (!switchFg_)
//			{
//				direction_ = { 2.0f, 0.0f };
//				if (liftPos.x >= maxPos_.x)
//				{
//					direction_ = { -2.0f, 0.0f };
//					switchFg_ = true;
//				}
//			}
//			else
//			{
//				direction_ = { -2.0f, 0.0f };
//				if (liftPos.x <= minPos_.x)
//				{
//					direction_ = { 2.0f, 0.0f };
//					switchFg_ = false;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonal:	// 斜め移動
//			if (!switchFg_)
//			{
//				direction_ = { 2.0f, 2.0f };
//				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
//				{
//					direction_ = { -2.0f, -2.0f };
//					switchFg_ = true;
//				}
//			}
//			else {
//				direction_ = { -2.0f, -2.0f };
//				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
//				{
//					direction_ = { 2.0f, 2.0f };
//					switchFg_ = false;
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
//	else
//	{
//		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//	}
//}
////--------------------------------------------------
//// @brief リフトに任意のオブジェクトが当たった時の処理
////--------------------------------------------------
//void Lift::OnCollisionEnter(GameObject* _other)
//{
//	switch (_other->GetType())
//	{
//	case GameObject::TypeID::Robot:
//		break;
//	case GameObject::TypeID::Tile:
//		break;
//	default:
//		break;
//	}
//}
////--------------------------------------------------
//// @brief リフトの正方向の最大座標を設定
////--------------------------------------------------
//void Lift::SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos)
//{
//	maxPos_ = _maxPos;
//}
////--------------------------------------------------
//// @brief リフトの負方向の最大座標を設定
////--------------------------------------------------
//void Lift::SetMinPos(DirectX::SimpleMath::Vector3 _minPos)
//{
//	minPos_ = _minPos;
//}
////--------------------------------------------------
//// @brief リフトに連動させたい振り子を設定
////--------------------------------------------------
//void Lift::SetPendulum(Pendulum* _pendulum)
//{
//	pendulum_ = _pendulum;
//	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
//}
////--------------------------------------------------
//// @brief リフトの移動状態を設定
////--------------------------------------------------
//void Lift::SetMoveState(Lift::MoveState _moveState)
//{
//	moveState_ = _moveState;
//}
