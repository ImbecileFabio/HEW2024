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
#include "../../PemdulumManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TimeZoneComponent/TimeZoneComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle)
	:GameObject(_gameManager, "Pendulum")
{
	this->InitGameObject();
	pendulum_component_->PendulumInit(_fulcrum, _movement, _pendulumAngle);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete pendulum_component_;
	delete collider_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"huriko/v02/ball_01.png");
	// �����蔻��R���|�[�l���g
	collider_component_ = new CircleColliderComponent(this);
	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumMovementComponent(this);
	// �g�����X�t�H�[���R���|�[�l���g
	transform_component_->SetScale(100.0f, 100.0f);
	// �C�x���g�ǉ�����
	collider_event_component_ = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
}
//--------------------------------------------------
// �����蔻��̎��s����
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
}
