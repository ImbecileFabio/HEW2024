//==================================================
// [Robot.cpp] ���{�b�g�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Robot.h"

#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "Lift.h"

#include "../Component.h"

#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/GravityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
	, robot_state_(RobotState::Idle)
{
	sprite_component_ = new SpriteComponent(this, "robot_still");
	velocity_component_ = new VelocityComponent(this);	// ���x
	gravity_component_ = new GravityComponent(this);	// �d��
	collider_component_ = new BoxColliderComponent(this);	// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);	// �����蔻��C�x���g
	robot_move_component_ = new RobotMoveComponent(this);	// ���{�b�g�ړ�
	push_out_component_ = new PushOutComponent(this);	// �����o��

	auto f = std::function<void(GameObject*)>(std::bind(&Robot::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);


	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Robot::~Robot(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
	delete velocity_component_;
	delete gravity_component_;
	delete robot_move_component_;
	delete push_out_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetSize(TILE_SIZE_X * 1.5, TILE_SIZE_Y * 1.5);
	collider_component_->SetSize(transform_component_->GetSize().x * 0.7, transform_component_->GetSize().y * 0.95);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

	// ���͏���
	InputManager& input = InputManager::GetInstance();

	//// �f�o�b�O�p�A���{�𑀍�ł���
	//// �ړ�����
	//if (input.GetKeyPress(VK_A))
	//{
	//	velocity_component_->SetVelocity(Vector3(-10, 0, 0));
	//}
	//else if (input.GetKeyPress(VK_D))
	//{
	//	velocity_component_->SetVelocity(Vector3(10, 0, 0));
	//}
	//else
	//{
	//	velocity_component_->SetVelocity(Vector3(0, 0, 0));
	//}

	// �}�E�X�N���b�N�ňړ�
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			  static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}


	switch (robot_state_)
	{
	case RobotState::Idle:	// �ҋ@���
	{
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN)) {
			robot_state_ = RobotState::Move;
		}
		break;
	}
	case RobotState::Move:	// �ړ����
	{
		if (!gravity_component_->GetIsGround()) {
			robot_state_ = RobotState::Fall;
		}
		break;
	}
	case RobotState::Fall:	// �������
	{
		if (gravity_component_->GetIsGround()) {
			robot_state_ = RobotState::Move;
		}
		break;
	}
	case RobotState::OnLift:	// ���t�g�ɏ���Ă�����
	{

		break;
	}
	}

	// ���{�b�g�̓�����؂�ւ���
	robot_move_component_->SetState(static_cast<RobotMoveComponent::RobotMoveState>(robot_state_));

}

void Robot::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		//std::cout << std::format("Robot -> Tile -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}

	case GameObject::TypeID::Lift:
	{
		//std::cout << std::format("Robot -> Lift -> OnCollisionEnter\n");
		
		auto lift = dynamic_cast<Lift*>(_other);

		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}

		// ���t�g�������Ă���Ȃ�
		if (lift->GetLiftState() == Lift::LiftState::Move)
		{
			robot_state_ = Robot::RobotState::OnLift;
		}
		else {
			robot_state_ = Robot::RobotState::Move;
		}

		velocity_component_->SetVelocity(lift->GetComponent<VelocityComponent>()->GetVelocity());
		break;
	}
	default:
		break;
	}
}
