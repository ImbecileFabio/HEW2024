#include "TimeZone.h"

#include "../GameObject/Robot.h"

#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/TimeZoneComponent.h"
#include "../Component/GimmickComponent/SmokeComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager, GameObject* _ownerPendulum)
	: GameObject(_gameManager, "TimeZone")
	, owner_pendulum_(_ownerPendulum)
{
	std::cout << std::format("��TimeZone�� -> Constructor\n");
	sprite_component_		 = new SpriteComponent(this, "timezone", 11);
	collider_base_component_ = new CircleColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);
	time_zone_component_ = new TimeZoneComponent(this, owner_pendulum_);

	auto f = std::function<void(GameObject*)>(std::bind(&TimeZone::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);

	InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
TimeZone::~TimeZone()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void TimeZone::InitGameObject(void)
{
	// �^�C���]�[���̎咣�����������C������̂œ����x�����Ă݂Ă܂�
	dynamic_cast<SpriteComponent*>(sprite_component_)->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void TimeZone::UpdateGameObject(void)
{
	time_zone_component_->SetTimeRateState(static_cast<TimeZoneComponent::TimeRateState>(state_));
}
//--------------------------------------------------
// @brief �^�C���]�[���̓����蔻��C�x���g����
//--------------------------------------------------
void TimeZone::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
	{
		auto robot = dynamic_cast<Robot*>(_other);

		// ���{�b�g�����t�g�ɏ���Ă���Ȃ�1�{��
		if (robot->GetRobotState() == Robot::RobotState::OnLift)
		{
			robot->GetComponent<VelocityComponent>()->SetSpeedRate(time_zone_component_->GetTimeRate());
			break;
		}



		auto robotVelocity = robot->GetComponent<VelocityComponent>();
		// ���x���܂��ύX����Ă��Ȃ��Ȃ�
		if (!robotVelocity->GetChangeSpeedRateFlg()) 
		{
			// ���̂܂ܑ��x��ύX
			robotVelocity->SetSpeedRate(time_zone_component_->GetTimeRate());
			robotVelocity->SetChangeSpeedRateFlg(true);
			break;
		}
		// �ύX���ꂽ���Ƃ���Ȃ�
		else
		{
			// �{���̍����ق�������
			if (robotVelocity->GetSpeedRate() < time_zone_component_->GetTimeRate())
			{
				robotVelocity->SetSpeedRate(time_zone_component_->GetTimeRate());
			}
		}

		break;
	}
	case GameObject::TypeID::Lift:
	{
		_other->GetComponent<VelocityComponent>()->SetSpeedRate(time_zone_component_->GetTimeRate());
		break;
	}
	case GameObject::TypeID::SmokePipe:
	{
		SmokeComponent* smoke = _other->GetComponent<SmokeComponent>();
		if (time_zone_component_->GetActiveFlg()) {
			smoke->SetTimeZoneFlg(true);
		}
		else {
			smoke->SetTimeZoneFlg(false);
		}
		break;
	}
	default:
		break;
	}
}

