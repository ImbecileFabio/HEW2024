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
#include "../Component/LiftComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
// @param _maxPos �������̍ő���W
// @param _minPos �������̍ő���W
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(Pendulum* _pendulum , LiftComponent::MoveState _moveState ,DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	velocity_component_ = new VelocityComponent(this);
	lift_component_ = new LiftComponent(_pendulum, _moveState, _maxPos, _minPos, this);
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
	delete sprite_component_;
	delete velocity_component_;
	delete lift_component_;
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
