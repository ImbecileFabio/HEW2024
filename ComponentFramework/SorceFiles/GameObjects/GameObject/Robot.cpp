//==================================================
// [Robot.cpp] ���{�b�g�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <algorithm>

#include "Robot.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
{
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
	delete velocity_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetPosition(0, -25);
	transform_component_->SetScale(150, 150);

	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"/robot_still_01.png");

	collider_component_ = new BoxColliderComponent(this);	// �����蔻��

	velocity_component_ = new VelocityComponent(this);	// ���x
	velocity_component_->SetUseGravity(false);


}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{
	auto& input =  InputManager::GetInstance();
	// �ړ�����
	if (input.GetKeyPress(VK_D))
	{
		velocity_component_->SetAcceleration(DirectX::SimpleMath::Vector3( 0.1f, 0.0f, 0.0f));
	}
	else if (input.GetKeyPress(VK_A))
	{
		velocity_component_->SetAcceleration(DirectX::SimpleMath::Vector3(-0.1f, 0.0f, 0.0f));
	}
	else
	{
		// �����x�̐�Βl���������Ɋ�Â��Č���������
		DirectX::SimpleMath::Vector3 current_acceleration = velocity_component_->GetAcceleration();
		if (current_acceleration.x > 0.0f)
		{
			current_acceleration.x = std::max(0.0f, current_acceleration.x - DECELERATION_RATE);
		}
		else if (current_acceleration.x < 0.0f)
		{
			current_acceleration.x = std::min(0.0f, current_acceleration.x + DECELERATION_RATE);
		}
		velocity_component_->SetAcceleration(current_acceleration);
	}

	

}