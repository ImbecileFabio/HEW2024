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
//--------------------------------------------------
// @brief コンストラクタ
// @param _maxPos 正方向の最大座標
// @param _minPos 負方向の最大座標
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	,moveState_(_moveState), maxPos_(_maxPos), minPos_(_minPos), switchFg_(false)
{
	spriteComponent_ = new SpriteComponent(this,"lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocityComponent_ = new VelocityComponent(this);
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
	delete spriteComponent_;
	delete velocityComponent_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	velocityComponent_->SetUseGravity(false);

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// 縦移動
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 0.0f, 2.0f, 0.0f });
				if (liftPos.y >= maxPos_.y) 
				{
					switchFg_ = true;
				}
			}
			else 
			{
				velocityComponent_->SetVelocity({ 0.0f, -2.0f, 0.0f });
				if (liftPos.y <= minPos_.y) 
				{
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// 横移動
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 2.0f, 0.0f, 0.0f });
				if (liftPos.x >= maxPos_.x)
				{
					switchFg_ = true;
				}
			}
			else 
			{
				velocityComponent_->SetVelocity({ -2.0f, 0.0f, 0.0f });
				if (liftPos.x <= minPos_.x)
				{
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonal:	// 斜め移動
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 2.0f, 2.0f, 0.0f });
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else {
				velocityComponent_->SetVelocity({ -2.0f, -2.0f, 0.0f });
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y) 
				{
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// リフトの座標を支点として渡し続ける
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocityComponent_->SetVelocity({ 0.0f, 0.0f, 0.0f });
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
