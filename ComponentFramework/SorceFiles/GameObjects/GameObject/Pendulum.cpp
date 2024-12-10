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
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TimeZoneComponent/TimeZoneComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/AngularVelocityComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Pendulum�� -> Constructor\n");
	this->InitGameObject();

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	std::cout << std::format("��Pendulum�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete pendulum_component_;
	delete collider_component_;
	delete time_zone_component_;
	delete angular_velocity_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"huriko/v01/ball_01.png");
	sprite_component_->SetObjectName("Pendulum");
	// �����蔻��R���|�[�l���g
	collider_component_ = new CircleColliderComponent(this);
	// �^�C���]�[���R���|�[�l���g
	time_zone_component_		= new TimeZoneComponent(this);
	angular_velocity_component_ = new AngularVelocityComponent(this);
	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumMovementComponent(this);
	transform_component_->SetScale(300.0f, 300.0f);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
