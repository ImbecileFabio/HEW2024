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
#include "../Component/LiftComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
// @param _maxPos 正方向の最大座標
// @param _minPos 負方向の最大座標
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(Pendulum* _pendulum , LiftComponent::MoveState _moveState ,DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	lift_component_ = new LiftComponent(_pendulum, _moveState, _maxPos, _minPos, this);
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
	delete sprite_component_;
	delete velocity_component_;
	delete lift_component_;
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
