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
#include "../Component/ChildrenComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
// @param _maxPos �������̍ő���W
// @param _minPos �������̍ő���W
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(GameManager* _gameManager)
	: GameObject(_gameManager, "Lift")
	, maxPos_(DirectX::SimpleMath::Vector3::Zero)
	, minPos_(DirectX::SimpleMath::Vector3::Zero)
	, direction_(0.0f, 0.0f)
	, moveState_(Lift::MoveState::length)
	, switchFg_(false)
{
	sprite_component_		  = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_  = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_		  = new VelocityComponent(this);
	velocity_component_->SetSpeedRate(2.0f);
	// �C�x���g�ǉ�����
	auto f = std::function<void(GameObject*)>(std::bind(&Lift::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
Lift::Lift(Lift::MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	: GameObject(_gameManager, "Lift")
	, maxPos_(_maxPos)
	, minPos_(_minPos)
	, direction_(0.0f, 0.0f)
	, moveState_(_moveState)
	, switchFg_(false)
{
	sprite_component_ = new SpriteComponent(this, "lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	velocity_component_->SetSpeedRate(2.0f);
	// ���t�g�̍��W�ŐU��q�𐶐�
	DirectX::SimpleMath::Vector3 pos = GetTransformComponent()->GetPosition();

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
	delete collider_base_component_;
	delete collider_event_component_;
	delete velocity_component_;
	delete sprite_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	transform_component_->SetSize(200.0f, 200.0f);
	velocity_component_->SetUseGravity(false);
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	if (!pendulum_) return;	// �U��q���ݒ肳��Ă��Ȃ��ꍇ�͏������s��Ȃ�
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();

	// �U��q�������Ă����烊�t�g�𓮂���
	if (moveFg)
	{	// ���t�g�̍��W�Ǝ擾
		DirectX::SimpleMath::Vector3 liftPos = GetTransformComponent()->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// �c�ړ�
			if (!switchFg_)
			{
				direction_ = Vector2(0.0f, 1.0f);
				if (liftPos.y >= maxPos_.y)
				{
					direction_ = Vector2(0.0f, -1.0f);
					switchFg_ = true;
				}
			}
			else
			{
				direction_ = Vector2(0.0f, -1.0f);
				if (liftPos.y <= minPos_.y)
				{
					direction_ = Vector2(0.0f, 1.0f);
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// ���ړ�
			if (!switchFg_)
			{
				direction_ = Vector2(1.0f, 0.0f);
				if (liftPos.x >= maxPos_.x)
				{
					direction_ = Vector2(-1.0f, 0.0f);
					switchFg_ = true;
				}
			}
			else
			{
				direction_ = Vector2(-1.0f, 0.0f);
				if (liftPos.x <= minPos_.x)
				{
					direction_ = Vector2(1.0f, 0.0f);
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonal:	// �΂߈ړ�
			if (!switchFg_)
			{
				direction_ = Vector2(1.0f, 1.0f);
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					direction_ = Vector2(-1.0f, -1.0f);
					switchFg_ = true;
				}
			}
			else {
				direction_ = Vector2(-1.0f, -1.0f);
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
				{
					direction_ = Vector2(1.0f, 1.0f);
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// �ŏI�I�Ȉړ�
		float speed = velocity_component_->GetSpeedRate();
		velocity_component_->SetVelocity(Vector3(direction_.x * speed, direction_.y * speed, 0.0f));
		// ���t�g�̍��W���x�_�Ƃ��ēn��������
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
// @brief ���t�g�̐������̍ő���W��ݒ�
//--------------------------------------------------
void Lift::SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos)
{
	maxPos_ = _maxPos;
}
//--------------------------------------------------
// @brief ���t�g�̕������̍ő���W��ݒ�
//--------------------------------------------------
void Lift::SetMinPos(DirectX::SimpleMath::Vector3 _minPos)
{
	minPos_ = _minPos;
}
//--------------------------------------------------
// @brief ���t�g�ƘA��������U��q��ݒ�
// @param _pendulum �A��������U��q
//--------------------------------------------------
void Lift::SetPendulum(Pendulum* _pendulum)
{
	pendulum_ = _pendulum;
	auto fulcrum = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
	transform_component_->SetPosition(fulcrum);
}
//--------------------------------------------------
// @brief ���t�g�̈ړ���Ԃ�ݒ�
//--------------------------------------------------
void Lift::SetMoveState(Lift::MoveState _moveState)
{
	moveState_ = _moveState;
}
