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

#include "../../GameProcess.h"	// window�T�C�Y�Ƃ邽�߂���
#include "../../GameManager.h"
#include "../Component.h"

#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"

// �f�o�b�O�p�R���|�[�l���g
#include "../Component/RenderComponent/DebugCollisionDrawComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/robot_still_01.png");
	collider_component_ = new BoxColliderComponent(this);	// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);	// �����蔻��C�x���g
	velocity_component_ = new VelocityComponent(this);	// ���x
	//robot_move_component_ = new RobotMoveComponent(this);	// ���{�b�g�ړ�
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
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -25);
	transform_component_->SetScale(150, 150);

	velocity_component_->SetUseGravity(true);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

	// ���͏���
	InputManager& input = InputManager::GetInstance();

	// �f�o�b�O�p�A���{�𑀍�ł���
	// �ړ�����
	if (input.GetKeyPress(VK_A))
	{
		velocity_component_->SetVelocity(Vector3(-10, 0, 0));
	}
	else if (input.GetKeyPress(VK_D))
	{
		velocity_component_->SetVelocity(Vector3(10, 0, 0));
	}
	else if (input.GetButtonPress(VK_W))
	{
		velocity_component_->SetVelocity(Vector3(0, 10, 0));
	}
	else if (input.GetButtonPress(VK_S))
	{
		velocity_component_->SetVelocity(Vector3(0, -10, 0));
	}
	else
	{
		velocity_component_->SetVelocity(Vector3(0, 0, 0));
	}

	// �}�E�X�N���b�N�ňړ�
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			  static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}


	// �d�͂�K�p�A
	velocity_component_->SetUseGravity(true);

}

void Robot::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		std::cout << std::format("Robot -> Tile -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}

	case GameObject::TypeID::Lift:
	{
		std::cout << std::format("Robot -> Lift -> OnCollisionEnter\n");
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}
	default:
		break;
	}
}
