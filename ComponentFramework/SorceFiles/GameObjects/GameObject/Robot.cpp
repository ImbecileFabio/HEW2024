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
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
{
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
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -25);
	//transform_component_->SetScale(150, 150);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/robot_still_01.png");

	collider_component_ = new BoxColliderComponent(this);	// 当たり判定

	collider_event_component_ = new ColliderEventComponent(this);	// 当たり判定イベント
	collider_event_component_->AddEvent([this](GameObject* _other)
		{
			this->OnCollisionEnter(_other);
		});

	velocity_component_ = new VelocityComponent(this);	// 速度
	velocity_component_->SetUseGravity(false);


}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{
	InputManager& input = InputManager::GetInstance();
	// 移動処理
	if (input.GetKeyPress(VK_D))
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3( 5.0f, 0.0f, 0.0f));
	}
	else if (input.GetKeyPress(VK_A))
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3(-5.0f, 0.0f, 0.0f));
	}
	else
	{
		velocity_component_->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	}

	if(collider_component_->GetHitFg())
	{
		sprite_component_->SetColor(Vector4(1.0f, 0.25f, 0.25f, 1.0f));
	}
	else
	{
		sprite_component_->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
}

void Robot::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
		std::cout << std::format("Robot -> Tile -> OnCollisionEnter\n");
		break;
	case GameObject::TypeID::Lift:
		std::cout << std::format("Robot -> Lift -> OnCollisionEnter\n");
		break;
	default:
		break;
	}
}
