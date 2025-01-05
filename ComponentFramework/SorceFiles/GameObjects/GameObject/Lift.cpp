//==================================================
// [Lift.cpp] ���t�g�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�I�u�W�F�N�g
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
Lift::Lift(GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, moveState_(MoveState::length)
	, startPos_(0.0f, 0.0f, 0.0f)
	, traveledDistance_(0.0f, 0.0f)
	, maxMoveDistance_(0.0f)
	, direction_(0.0f, 0.0f)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
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
// @param _moveDistance �ő�ړ�����
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(MoveState _moveState, float _moveDistance, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	, moveState_(_moveState)
	, traveledDistance_(0.0f, 0.0f)
	, maxMoveDistance_(_moveDistance)
	, direction_(0.0f, 0.0f)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this,"lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	// �C�x���g�ǉ�����
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
	// ���t�g�̊J�n���W���擾
	startPos_ = transform_component_->GetPosition();

	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Lift::~Lift()
{
	delete collider_base_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	velocity_component_->SetUseGravity(false);

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// �c�ړ�
			if (!switchFg_) 
			{
				// ��Ɉړ�
				direction_ = { 0.0f, 1.0f };
				// �ړ�������ݐ�
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.y >= maxMoveDistance_)
				{
					// �t�����Ɉړ�
					direction_ = { 0.0f, -1.0f };
					traveledDistance_.y = 0.0f;
					switchFg_ = true;
				}
			}
			else 
			{
				// ���Ɉړ�
				direction_ = { 0.0f, -1.0f };
				// �ړ�������ݐ�
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.y >= maxMoveDistance_) 
				{
					// �t�����Ɉړ�
					direction_ = { 0.0f, 1.0f };
					traveledDistance_.y = 0.0f;
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// ���ړ�
			if (!switchFg_) 
			{
				// �E�Ɉړ�
				direction_ = { 1.0f, 0.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_)
				{
					direction_ = { -1.0f, 0.0f };	// �t�����Ɉړ�
					traveledDistance_.x = 0.0f;
					switchFg_ = true;
				}
			}
			else 
			{
				// ���Ɉړ�
				direction_ = { -1.0f, 0.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_)
				{
					direction_ = { 1.0f, 0.0f };	// �t�����Ɉړ�
					traveledDistance_.x = 0.0f;
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonalRight:	// �΂߈ړ��i�E�j
			if (!switchFg_)
			{
				// �E��Ɉړ�
				direction_ = { 1.0f, 1.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { -1.0f, -1.0f };
					switchFg_ = true;
				}
			}
			else
			{
				// �����Ɉړ�
				direction_ = { -1.0f, -1.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { 1.0f, 1.0f };
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonalLeft:	// �΂߈ړ��i���j
			if (!switchFg_)
			{
				// ����Ɉړ�
				direction_ = { -1.0f, 1.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { 1.0f, -1.0f };
					switchFg_ = true;
				}
			}
			else
			{
				// �E���Ɉړ�
				direction_ = { 1.0f, -1.0f };
				// �ړ�������ݐ�
				traveledDistance_.x += std::abs(direction_.x);
				traveledDistance_.y += std::abs(direction_.y);
				// �ړ��������ő�ړ������𒴂�����
				if (traveledDistance_.x >= maxMoveDistance_ && traveledDistance_.y >= maxMoveDistance_)
				{
					traveledDistance_ = { 0.0f, 0.0f };
					direction_ = { -1.0f, 1.0f };
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// ���t�g�̍��W���x�_�Ƃ��ēn��������
		velocity_component_->SetVelocity(Vector3(direction_.x , direction_.y, 0.0f));
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
	}
}
//--------------------------------------------------
// @brief ���t�g�ɔC�ӂ̃I�u�W�F�N�g�������������̏���
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
void Lift::SetMoveState(Lift::MoveState _moveState)
{
	moveState_ = _moveState;
}

//Lift::Lift(GameManager* _gameManager)
//	:GameObject(_gameManager, "Lift")
//	, moveState_(MoveState::length)
//	, maxPos_(0.0f, 0.0f, 0.0f)
//	, direction_(0.0f, 0.0f)
//	, minPos_(0.0f, 0.0f, 0.0f)
//	, switchFg_(false)
//{
//	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
//	collider_base_component_ = new BoxColliderComponent(this);
//	collider_event_component_ = new ColliderEventComponent(this);
//	velocity_component_ = new VelocityComponent(this);
//	// �C�x���g�ǉ�����
//	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
//	collider_event_component_->AddEvent(f);
//	this->InitGameObject();
//}
////--------------------------------------------------
//// @brief �R���X�g���N�^
//// @param _maxPos �������̍ő���W
//// @param _minPos �������̍ő���W
//// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
////--------------------------------------------------
//Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
//	:GameObject(_gameManager, "Lift")
//	, moveState_(_moveState)
//	, maxPos_(_maxPos)
//	, direction_(0.0f, 0.0f)
//	, minPos_(_minPos)
//	, switchFg_(false)
//{
//	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
//	collider_base_component_ = new BoxColliderComponent(this);
//	collider_event_component_ = new ColliderEventComponent(this);
//	velocity_component_ = new VelocityComponent(this);
//	// �C�x���g�ǉ�����
//	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
//	collider_event_component_->AddEvent(f);
//
//	this->InitGameObject();
//}
////--------------------------------------------------
//// @brief �f�X�g���N�^
////--------------------------------------------------
//Lift::~Lift()
//{
//	delete collider_base_component_;
//	delete collider_event_component_;
//	delete sprite_component_;
//	delete velocity_component_;
//}
////--------------------------------------------------
//// @brief ����������
////--------------------------------------------------
//void Lift::InitGameObject(void)
//{
//	velocity_component_->SetUseGravity(false);
//
//}
////--------------------------------------------------
//// @brief �X�V����
////--------------------------------------------------
//void Lift::UpdateGameObject(void)
//{
//	if (!pendulum_) return;
//	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
//	if (moveFg)
//	{
//		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
//		switch (moveState_)
//		{
//		case Lift::MoveState::length:	// �c�ړ�
//			if (!switchFg_)
//			{
//				direction_ = { 0.0f, 2.0f };
//				if (liftPos.y >= maxPos_.y)
//				{
//					direction_ = { 0.0f, -2.0f };
//					switchFg_ = true;
//				}
//			}
//			else
//			{
//				direction_ = { 0.0f, -2.0f };
//				if (liftPos.y <= minPos_.y)
//				{
//					direction_ = { 0.0f, 2.0f };
//					switchFg_ = false;
//				}
//			}
//			break;
//		case Lift::MoveState::side:		// ���ړ�
//			if (!switchFg_)
//			{
//				direction_ = { 2.0f, 0.0f };
//				if (liftPos.x >= maxPos_.x)
//				{
//					direction_ = { -2.0f, 0.0f };
//					switchFg_ = true;
//				}
//			}
//			else
//			{
//				direction_ = { -2.0f, 0.0f };
//				if (liftPos.x <= minPos_.x)
//				{
//					direction_ = { 2.0f, 0.0f };
//					switchFg_ = false;
//				}
//			}
//			break;
//		case Lift::MoveState::diagonal:	// �΂߈ړ�
//			if (!switchFg_)
//			{
//				direction_ = { 2.0f, 2.0f };
//				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
//				{
//					direction_ = { -2.0f, -2.0f };
//					switchFg_ = true;
//				}
//			}
//			else {
//				direction_ = { -2.0f, -2.0f };
//				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
//				{
//					direction_ = { 2.0f, 2.0f };
//					switchFg_ = false;
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
//	else
//	{
//		velocity_component_->SetVelocity({ 0.0f, 0.0f, 0.0f });
//	}
//}
////--------------------------------------------------
//// @brief ���t�g�ɔC�ӂ̃I�u�W�F�N�g�������������̏���
////--------------------------------------------------
//void Lift::OnCollisionEnter(GameObject* _other)
//{
//	switch (_other->GetType())
//	{
//	case GameObject::TypeID::Robot:
//		break;
//	case GameObject::TypeID::Tile:
//		break;
//	default:
//		break;
//	}
//}
////--------------------------------------------------
//// @brief ���t�g�̐������̍ő���W��ݒ�
////--------------------------------------------------
//void Lift::SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos)
//{
//	maxPos_ = _maxPos;
//}
////--------------------------------------------------
//// @brief ���t�g�̕������̍ő���W��ݒ�
////--------------------------------------------------
//void Lift::SetMinPos(DirectX::SimpleMath::Vector3 _minPos)
//{
//	minPos_ = _minPos;
//}
////--------------------------------------------------
//// @brief ���t�g�ɘA�����������U��q��ݒ�
////--------------------------------------------------
//void Lift::SetPendulum(Pendulum* _pendulum)
//{
//	pendulum_ = _pendulum;
//	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
//}
////--------------------------------------------------
//// @brief ���t�g�̈ړ���Ԃ�ݒ�
////--------------------------------------------------
//void Lift::SetMoveState(Lift::MoveState _moveState)
//{
//	moveState_ = _moveState;
//}
