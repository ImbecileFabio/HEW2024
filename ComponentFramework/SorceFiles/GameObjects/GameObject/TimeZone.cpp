#include "TimeZone.h"

#include "../GameObject/Robot.h"
#include "../GameObject/Lift.h"

#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/TimeZoneComponent.h"
#include "../Component/GimmickComponent/SmokeComponent.h"
#include "../Component/GimmickComponent/LiftInteractionComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager, GameObject* _ownerPendulum, int _order)
	: GameObject(_gameManager, "TimeZone", _order)
	, owner_pendulum_(_ownerPendulum)
{
	sprite_component_ = new SpriteComponent(this, "timezone", 10);
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
	dynamic_cast<SpriteComponent*>(sprite_component_)->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.4f));
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
	{

		auto robotVelocity = _other->GetComponent<VelocityComponent>();
		if (!robotVelocity) return;

		if (auto liftInteraction = _other->GetComponent<LiftInteractionComponent>())
		{
			// リフトに乗っていたら処理しない
			if (liftInteraction->GetLift()) { return; }

			// 速度がまだ変更されていないなら
			if (!robotVelocity->GetChangeSpeedRateFlg())
			{
				// そのまま速度を変更
				robotVelocity->SetSpeedRate(time_zone_component_->GetTimeRate());
				robotVelocity->SetChangeSpeedRateFlg(true);
				break;
			}
			// 変更されたことあるなら
			else
			{
				// 倍率の高いほうをつかう
				if (robotVelocity->GetSpeedRate() < time_zone_component_->GetTimeRate())
				{
					robotVelocity->SetSpeedRate(time_zone_component_->GetTimeRate());
				}
			}

			break;
		}
	}
	case GameObject::TypeID::Lift:
	{
		auto velocity = _other->GetComponent<VelocityComponent>();
		if (!velocity) return;
		// 速度がまだ変更されていないなら

		if (!velocity->GetChangeSpeedRateFlg())
		{
			// そのまま速度を変更
			velocity->SetSpeedRate(time_zone_component_->GetTimeRate());
			velocity->SetChangeSpeedRateFlg(true);
			break;
		}
		// 変更されたことあるなら
		else
		{
			// 倍率の高いほうをつかう
			if (velocity->GetSpeedRate() < time_zone_component_->GetTimeRate())
			{
				velocity->SetSpeedRate(time_zone_component_->GetTimeRate());
			}
		}

		break;
	}
	case GameObject::TypeID::SmokePipe:
	{
		SmokeComponent* smoke = _other->GetComponent<SmokeComponent>();
		smoke->SetTimeZoneHitFlg(true);
		if (time_zone_component_->GetActiveFlg()) {
			smoke->SetTimeZoneONFlg(true);
			switch (state_)
			{
			case TimeZone::TimeZoneState::Slow:
				smoke->SetTimeSpeed(0.5f);
				break;
			case TimeZone::TimeZoneState::Normal:
				smoke->SetTimeSpeed(1.0f);
				break;
			case TimeZone::TimeZoneState::Fast:
				smoke->SetTimeSpeed(1.5f);
				break;
			default:
				break;
			}
		}
		else {
			smoke->SetTimeZoneONFlg(false);
		}
		break;
	}
	default:
		break;
	}
}
