//==================================================
// [Pendulum.cpp] 振り子オブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：振り子の処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Pendulum.h"
#include "TimeZone.h"
#include "Stick.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TimeZoneComponent/TimeZoneComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ChildrenComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager, "Pendulum")
{
	this->InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete pendulum_component_;
	delete collider_component_;
	delete children_component_;
	delete stick_;
	delete timeZone_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"huriko/v02/ball_01.png");
	// 当たり判定コンポーネント
	collider_component_ = new CircleColliderComponent(this);
	// 振り子コンポーネント
	pendulum_component_ = new PendulumMovementComponent(this);
	pendulum_component_->SetPendulumAngle(60.0f);
	pendulum_component_->PendulumInit(0.1f, Vector3(0.0f, 0.0f, 0.0f), 200.0f);
	// トランスフォームコンポーネント
	transform_component_->SetScale(100.0f, 100.0f);

	// イベント追加
	collider_event_component = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component->AddEvent(f);


	// 子オブジェクトの追加
	timeZone_ = new TimeZone(game_manager_);
	stick_ = new Stick(game_manager_);

	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(timeZone_);
	children_component_->AddChild(stick_);
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
//--------------------------------------------------
// 振り子の当たった時の処理
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	//auto pendulumMovementComponent = _other->GetComponent<PendulumMovementComponent>();
	switch (_other->GetType())
	{
	case GameObject::TypeID::TimeZone:
		
		break;
	case GameObject::TypeID::Pendulum:
		// 振り子の動きを取得
		// 振り子の状態が止まっている状態だったら
		if (_other->GetComponent<PendulumMovementComponent>()->GetPendulumState()
			== PendulumMovementComponent::PendulumState::stop)
		{	// 動く状態に変更
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumState(PendulumMovementComponent::PendulumState::move);
		}
		break;
	default:
		break;
	}
}
