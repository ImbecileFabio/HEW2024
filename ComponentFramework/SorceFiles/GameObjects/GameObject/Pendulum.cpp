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
#include "../../GameManager.h"
#include "../../PemdulumManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ChildrenComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle)
	:GameObject(_gameManager, "Pendulum")
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, "ball");
	// 当たり判定コンポーネント
	collider_component_ = new CircleColliderComponent(this);
	// 振り子コンポーネント
	pendulum_component_ = new PendulumMovementComponent(this);
	// 子タイムゾーン
	time_zone_ = new TimeZone(game_manager_);
	// 子オブジェクト管理コンポーネント
	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(time_zone_);

	// イベント追加処理
	collider_event_component_ = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	pendulum_component_->PendulumInit(_fulcrum, _movement, _pendulumAngle);
	this->InitGameObject();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete pendulum_component_;
	delete children_component_;
	delete collider_event_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	auto pos = pendulum_component_->GetPendulumFulcrum();
	time_zone_->GetTransformComponent()->SetPosition(pos.x, pos.y);
}
//--------------------------------------------------
// 当たり判定の実行処理
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	bool moveFg = false;
	switch (_other->GetType())
	{
	case GameObject::TypeID::Pendulum:
		moveFg = _other->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
		// 振り子が止まっていたら
		if ((!moveFg)&&_other->GetComponent<PendulumMovementComponent>()->GetPendulumAngle() == 0)
		{
			// 振り子の動きを開始
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumMovement(true);
			_other->GetComponent<PendulumMovementComponent>()->StartPendulumMovement();
		}
		break;
	default:
		break;
	}
}