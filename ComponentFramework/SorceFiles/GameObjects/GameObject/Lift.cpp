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
//--------------------------------------------------
// @brief �R���X�g���N�^
// @param _maxPos �������̍ő���W
// @param _minPos �������̍ő���W
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	,moveState_(_moveState), maxPos_(_maxPos), minPos_(_minPos), switchFg_(false)
{
	spriteComponent_ = new SpriteComponent(this,"lift_floor_center");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocityComponent_ = new VelocityComponent(this);
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
	delete spriteComponent_;
	delete velocityComponent_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	velocityComponent_->SetUseGravity(false);

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = transform_component_->GetPosition();
		switch (moveState_)
		{
		case Lift::MoveState::length:	// �c�ړ�
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 0.0f, 2.0f, 0.0f });
				if (liftPos.y >= maxPos_.y) 
				{
					switchFg_ = true;
				}
			}
			else 
			{
				velocityComponent_->SetVelocity({ 0.0f, -2.0f, 0.0f });
				if (liftPos.y <= minPos_.y) 
				{
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::side:		// ���ړ�
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 2.0f, 0.0f, 0.0f });
				if (liftPos.x >= maxPos_.x)
				{
					switchFg_ = true;
				}
			}
			else 
			{
				velocityComponent_->SetVelocity({ -2.0f, 0.0f, 0.0f });
				if (liftPos.x <= minPos_.x)
				{
					switchFg_ = false;
				}
			}
			break;
		case Lift::MoveState::diagonal:	// �΂߈ړ�
			if (!switchFg_) 
			{
				velocityComponent_->SetVelocity({ 2.0f, 2.0f, 0.0f });
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else {
				velocityComponent_->SetVelocity({ -2.0f, -2.0f, 0.0f });
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y) 
				{
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// ���t�g�̍��W���x�_�Ƃ��ēn��������
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocityComponent_->SetVelocity({ 0.0f, 0.0f, 0.0f });
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
