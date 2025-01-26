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
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/GimmickComponent/LiftComponent.h"
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

// �܂��e�X�g�i�K�Ȃ̂ŃR�����g�A�E�g�����Ă����܂�, by arima
////--------------------------------------------------
//// @brief �X�V����
////--------------------------------------------------
//void Lift::UpdateGameObject(void)
//{
//	if (!pendulum_) return;
//
//	// �؂�ւ�����莞�Ԓ�~����
//	switch (lift_state_)
//	{
//	case Lift::LiftState::Stop:
//	{
//		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//
//		if (turn_count_ >= 180) {
//			if (pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement())
//			{
//				lift_state_ = Lift::LiftState::Move;
//				turn_count_ = 0;
//			}
//		}
//		else {
//			++turn_count_;
//		}
//
//		return;
//		break;
//	}
//	case Lift::LiftState::Move:
//	{
//		if (!pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement())
//		{
//			lift_state_ = Lift::LiftState::Stop;
//			velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//			turn_count_ = 180;
//			return;
//		}
//
//		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
//		switch (moveState_)
//		{
//		case Lift::MoveState::length:	// �c�ړ�
//			if (!switchFg_)
//			{
//				// ��Ɉړ�
//				direction_ = { 0.0f, 1.0f };
//				// �ړ�������ݐ�
//				traveledDistance_.y += std::abs(direction_.y) * velocity_component_->GetSpeedRate();
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.y >= maxMoveDistance_)
//				{
//					// �t�����Ɉړ�
//					direction_ = { 0.0f, -1.0f };
//					traveledDistance_.y = 0.0f;
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// ���Ɉړ�
//				direction_ = { 0.0f, -1.0f };
//				// �ړ�������ݐ�
//				traveledDistance_.y += std::abs(direction_.y) * velocity_component_->GetSpeedRate();
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.y >= maxMoveDistance_)
//				{
//					// �t�����Ɉړ�
//					direction_ = { 0.0f, 1.0f };
//					traveledDistance_.y = 0.0f;
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::side:		// ���ړ�
//			if (!switchFg_)
//			{
//				// �E�Ɉړ�
//				direction_ = { 1.0f, 0.0f };
//				// �ړ�������ݐ�
//				traveledDistance_.x += std::abs(direction_.x) * velocity_component_->GetSpeedRate();
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_)
//				{
//					direction_ = { -1.0f, 0.0f };	// �t�����Ɉړ�
//					traveledDistance_.x = 0.0f;
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// ���Ɉړ�
//				direction_ = { -1.0f, 0.0f };
//				// �ړ�������ݐ�
//				traveledDistance_.x += std::abs(direction_.x) * velocity_component_->GetSpeedRate();
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_)
//				{
//					direction_ = { 1.0f, 0.0f };	// �t�����Ɉړ�
//					traveledDistance_.x = 0.0f;
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonalRight:	// �΂߈ړ��i�E�j
//			if (!switchFg_)
//			{
//				// �E��Ɉړ�
//				direction_ = { 1.0f, 1.0f };
//				// �ړ�������ݐ�
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { -1.0f, -1.0f };
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// �����Ɉړ�
//				direction_ = { -1.0f, -1.0f };
//				// �ړ�������ݐ�
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { 1.0f, 1.0f };
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonalLeft:	// �΂߈ړ��i���j
//			if (!switchFg_)
//			{
//				// ����Ɉړ�
//				direction_ = { -1.0f, 1.0f };
//				// �ړ�������ݐ�
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { 1.0f, -1.0f };
//					switchFg_ = true;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			else
//			{
//				// �E���Ɉړ�
//				direction_ = { 1.0f, -1.0f };
//				// �ړ�������ݐ�
//				Vector2 normalizedDirection = {
//					direction_.x / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y),
//					direction_.y / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y)
//				};
//				traveledDistance_.x += std::abs(normalizedDirection.x) * velocity_component_->GetSpeedRate();
//				traveledDistance_.y += std::abs(normalizedDirection.y) * velocity_component_->GetSpeedRate();
//
//				// �ړ��������ő�ړ������𒴂�����
//				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
//				{
//					traveledDistance_ = { 0.0f, 0.0f };
//					direction_ = { -1.0f, 1.0f };
//					switchFg_ = false;
//					lift_state_ = Lift::LiftState::Stop;
//				}
//			}
//			break;
//		default:
//			break;
//		}
//		// ���t�g�̍��W���x�_�Ƃ��ēn��������
//		velocity_component_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
//		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
//	}
//	}
//}

//--------------------------------------------------
// @brief ���t�g�ɔC�ӂ̃I�u�W�F�N�g�������������̏���
//--------------------------------------------------
void Lift::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		_other->GetComponent<VelocityComponent>()->SetVelocity(this->velocity_component_->GetVelocity());
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