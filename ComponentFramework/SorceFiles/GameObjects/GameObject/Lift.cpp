//==================================================
// [Lift.cpp] ���t�g�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�֌W��State�Ǘ��Ȃǂ��s�����Ƃɂ��Ă܂�
//==================================================
/*----- �C���N���[�h -----*/
#include <algorithm>
#include "Lift.h"
#include "Pendulum.h"
#include "Robot.h"

#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/GimmickComponent/LiftComponent.h"
#include "../Component/GimmickComponent/LiftInteractionComponent.h"
#include "Gimmick/Group/LiftGroup.h"

Lift::Lift(GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, lift_state_(Lift::LiftState::Stop)
	, move_state_(MoveState::length)
	, turn_count_(0)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);


	// �C�x���g�ǉ�����
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �R���X�g���N�^
// @param _moveState �ړ����
// @param _endPos �؂�Ԃ��n�_
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(GameManager* _gameManager, MoveState _moveState, Vector3 _startPos, Vector3 _endPos, Pendulum* _pendulum)
	:GameObject(_gameManager, "Lift")
	, pendulum_(_pendulum)
	, turn_count_(0)
	, lift_state_(Lift::LiftState::Stop)
	, move_state_(_moveState)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	lift_component_ = new LiftComponent(this, static_cast<LiftComponent::LiftComMoveState>(move_state_), _startPos, _endPos, pendulum_);
	// �C�x���g�ǉ�����
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Lift::~Lift()
{
	delete collider_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	lift_state_ = Lift::LiftState::Stop;
	turn_count_ = 0;
}


//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;

	// �U��q�������Ă��邩�ǂ���
	auto pendulumMoveFlg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();

	switch (lift_state_) 
	{
	case Lift::LiftState::Stop:
	{
		// �J�E���g��0�ɂȂ����玟�̏�ԂɑJ��
		if (turn_count_  <= 0) {
			if (pendulumMoveFlg)
			{
				lift_state_ = Lift::LiftState::Move;
				turn_count_ = 180;
			}
		}
		else {
			--turn_count_;
		}
		break;
	}
	case Lift::LiftState::Move:
	{
		if (!pendulumMoveFlg)
		{
			lift_state_ = Lift::LiftState::Stop;
			turn_count_ = 0;	// �ړ����Ɏ~�܂����玟�����Ƃ��͂�����������悤��
		}

		// ���t�g�̈ړ��������ő勗���𒴂�����؂�Ԃ�
		if (lift_component_->CheckTraveledDistance()) {
			lift_state_ = Lift::LiftState::Stop;
		}
		break;
	}
	}
	// state���Z�b�g
	lift_component_->SetLiftComState(static_cast<LiftComponent::LiftComState>(lift_state_));
	// �O���[�v�̃^�C���𑵂��鏈��
	lift_group_->UpdateLiftTilePositions();
}


//--------------------------------------------------
// @brief ���t�g�ɔC�ӂ̃I�u�W�F�N�g�������������̏���
//--------------------------------------------------
void Lift::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		if (auto robot = dynamic_cast<Robot*>(_other))
		{
			if (auto interaction = robot->GetComponent<LiftInteractionComponent>())
			{
				// ���{�b�g�Ƀ��t�g���Z�b�g
				interaction->SetLift(this);
			}
		}
		break;
	case GameObject::TypeID::Tile:
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// @brief ���t�g�ɘA�����������U��q��ݒ�
//--------------------------------------------------
void Lift::SetPendulum(Pendulum* _pendulum)
{
	pendulum_ = _pendulum;
	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
}
//--------------------------------------------------
// @brief ���t�g�̈ړ���Ԃ�ݒ�
//--------------------------------------------------
void Lift::SetMoveState(Lift::MoveState _state)
{
	move_state_ = _state;
}