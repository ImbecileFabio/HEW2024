//==================================================
// [Lift.cpp] リフトファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトオブジェクト
//==================================================
/*----- インクルード -----*/
#include <algorithm>
#include "Lift.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"

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
	std::cout << std::format("＜Lift＞ -> Constructor\n");
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Lift::~Lift()
{
	std::cout << std::format("＜Lift＞ -> Destructor\n");
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
	transform_component_->SetScale(200.0f, 100.0f);
	transform_component_->SetPosition(0.0f, 0.0f);

	spriteComponent_   = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocityComponent_ = new VelocityComponent(this);

	velocityComponent_->SetUseGravity(false);
	// イベント追加処理
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(4, f);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	DirectX::SimpleMath::Vector3 pos = this->transform_component_->GetPosition();
	switch (moveState_)
	{
	case Lift::MoveState::length:	// 縦移動
		if (pos.y <= maxPos_.y && switchFg_ == false)
		{
			velocityComponent_->SetVelocity	   ({ 0.0f, 2.0f, 0.0f });
			if (pos.y >= maxPos_.y)
				switchFg_ = true;
		}
		if (pos.y >= minPos_.y && switchFg_ == true)
		{
			velocityComponent_->SetVelocity	   ({ 0.0f, -2.0f, 0.0f });
			if (pos.y <= minPos_.y)
				switchFg_ = false;
		}
		break;
	case Lift::MoveState::side:		// 横移動
		if (pos.x <= maxPos_.x && switchFg_ == false)
		{
			velocityComponent_->SetVelocity	   ({ 2.0f, 0.0f, 0.0f });
			if (pos.x >= maxPos_.x)
				switchFg_ = true;
		}
		if (pos.x >= minPos_.x && switchFg_ == true)
		{
			velocityComponent_->SetVelocity	   ({ -2.0f, 0.0f, 0.0f });
			if (pos.x <= minPos_.x)
				switchFg_ = false;
		}
		break;
	default:
		break;
	}
	this->transform_component_->SetPosition(pos);
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
