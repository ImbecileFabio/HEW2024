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
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle)
	:GameObject(_gameManager, "Pendulum")
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, "ball");
	// �����蔻��R���|�[�l���g
	collider_component_ = new CircleColliderComponent(this);
	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumMovementComponent(this);
	// �q�^�C���]�[��
	time_zone_ = new TimeZone(game_manager_);
	// �q�I�u�W�F�N�g�Ǘ��R���|�[�l���g
	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(time_zone_);

	// �C�x���g�ǉ�����
	collider_event_component_ = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	pendulum_component_->PendulumInit(_fulcrum, _movement, _pendulumAngle);
	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete pendulum_component_;
	delete children_component_;
	delete collider_event_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	auto pos = pendulum_component_->GetPendulumFulcrum();
	time_zone_->GetTransformComponent()->SetPosition(pos.x, pos.y);
}
//--------------------------------------------------
// �����蔻��̎��s����
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	bool moveFg = false;
	switch (_other->GetType())
	{
	case GameObject::TypeID::Pendulum:
		moveFg = _other->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
		// �U��q���~�܂��Ă�����
		if ((!moveFg)&&_other->GetComponent<PendulumMovementComponent>()->GetPendulumAngle() == 0)
		{
			// �U��q�̓������J�n
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumMovement(true);
			_other->GetComponent<PendulumMovementComponent>()->StartPendulumMovement();
		}
		break;
	default:
		break;
	}
}