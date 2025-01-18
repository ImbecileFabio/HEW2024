#include "TimeZone.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/TimeZoneComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager, GameObject* _ownerPendulum)
	: GameObject(_gameManager, "TimeZone")
	, owner_pendulum_(_ownerPendulum)
{
	std::cout << std::format("＜TimeZone＞ -> Constructor\n");
	sprite_component_		 = new SpriteComponent(this, "timezone");
	collider_base_component_ = new CircleColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);
	time_zone_component_ = new TimeZoneComponent(this, owner_pendulum_);

	auto f = std::function<void(GameObject*)>(std::bind(&TimeZone::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);

	InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
TimeZone::~TimeZone()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void TimeZone::InitGameObject(void)
{
	// タイムゾーンの主張が少し強い気がするので透明度下げてみてます
	dynamic_cast<SpriteComponent*>(sprite_component_)->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void TimeZone::UpdateGameObject(void)
{
	time_zone_component_->SetTimeRateState(static_cast<TimeZoneComponent::TimeRateState>(state_));
}
//--------------------------------------------------
// @brief タイムゾーンの当たり判定イベント処理
//--------------------------------------------------
void TimeZone::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		_other->GetComponent<VelocityComponent>()->SetSpeedRate(time_zone_component_->GetTimeRate());
		break;
	case GameObject::TypeID::Lift:
		_other->GetComponent<VelocityComponent>()->SetSpeedRate(time_zone_component_->GetTimeRate());
		break;
	default:
		break;
	}
}

