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
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TimeZoneComponent/TimeZoneComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/AngularVelocityComponent.h"

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
	delete time_zone_component_;
	delete angular_velocity_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"huriko/v01/ball_01.png");
	// 当たり判定コンポーネント
	collider_component_ = new CircleColliderComponent(this);
	// タイムゾーンコンポーネント
	time_zone_component_		= new TimeZoneComponent(this);
	angular_velocity_component_ = new AngularVelocityComponent(this);
	// 振り子コンポーネント
	pendulum_component_ = new PendulumMovementComponent(this);
	pendulum_component_->SetPendulumAngle(60.0f);
	transform_component_->SetScale(300.0f, 300.0f);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	this->pendulum_component_->Update(0.01f, Vector3(0.0f, 0.0f, 0.0f), 200.0f);
}
