//==================================================
// [Pendulum.cpp] �U��q�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̏������`
//==================================================

/*----- �C���N���[�h -----*/
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
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager, "Pendulum")
{
	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete pendulum_component_;
	delete collider_component_;
	delete children_component_;
	delete stick_;
	delete timeZone_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"huriko/v02/ball_01.png");
	// �����蔻��R���|�[�l���g
	collider_component_ = new CircleColliderComponent(this);
	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumMovementComponent(this);
	pendulum_component_->SetPendulumAngle(60.0f);
	pendulum_component_->PendulumInit(0.1f, Vector3(0.0f, 0.0f, 0.0f), 200.0f);
	// �g�����X�t�H�[���R���|�[�l���g
	transform_component_->SetScale(100.0f, 100.0f);

	// �C�x���g�ǉ�
	collider_event_component = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component->AddEvent(f);


	// �q�I�u�W�F�N�g�̒ǉ�
	timeZone_ = new TimeZone(game_manager_);
	stick_ = new Stick(game_manager_);

	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(timeZone_);
	children_component_->AddChild(stick_);
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
//--------------------------------------------------
// �U��q�̓����������̏���
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	//auto pendulumMovementComponent = _other->GetComponent<PendulumMovementComponent>();
	switch (_other->GetType())
	{
	case GameObject::TypeID::TimeZone:
		
		break;
	case GameObject::TypeID::Pendulum:
		// �U��q�̓������擾
		// �U��q�̏�Ԃ��~�܂��Ă����Ԃ�������
		if (_other->GetComponent<PendulumMovementComponent>()->GetPendulumState()
			== PendulumMovementComponent::PendulumState::stop)
		{	// ������ԂɕύX
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumState(PendulumMovementComponent::PendulumState::move);
		}
		break;
	default:
		break;
	}
}
