//==================================================
// [Lift.cpp] ���t�g�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�I�u�W�F�N�g
//==================================================
/*----- �C���N���[�h -----*/
#include <algorithm>
#include "Lift.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
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
	std::cout << std::format("��Lift�� -> Constructor\n");
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Lift::~Lift()
{
	std::cout << std::format("��Lift�� -> Destructor\n");
	delete collider_base_component;
	delete event_base_component;
	delete spriteComponent_;
	delete velocityComponent_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	this->spriteComponent_   = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png", 0);
	this->collider_base_component = new CircleColliderComponent(this);
	this->event_base_component = new ColliderEventComponent(this);
	this->velocityComponent_ = new VelocityComponent(this);

	this->transform_component_->SetScale(300.0f, 300.0f);
	this->transform_component_->SetPosition(0.0f, 0.0f);

	this->velocityComponent_->SetUseGravity(false);
	// �C�x���g�ǉ�����
	this->event_base_component->AddEvent([this](GameObject* _other) 
		{
		this->OnCollisionEnter(_other);
		});
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	DirectX::SimpleMath::Vector3 pos = this->transform_component_->GetPosition();
	switch (moveState_)
	{
	case Lift::MoveState::length:	// �c�ړ�
		if (pos.y <= maxPos_.y && switchFg_ == false)
		{
			velocityComponent_->SetVelocity	   ({ 0.0f, 2.0f, 0.0f });
			if (pos.y >= maxPos_.y)
				switchFg_ = true;
		}
		if (pos.y >= minPos_.y && switchFg_ == true)
		{
			velocityComponent_->SetVelocity	   ({ 0.0f, -2.0f, 0.0f });
			if (pos.y <= minPos_.y)
				switchFg_ = false;
		}
		break;
	case Lift::MoveState::side:		// ���ړ�
		if (pos.x <= maxPos_.x && switchFg_ == false)
		{
			velocityComponent_->SetVelocity	   ({ 2.0f, 0.0f, 0.0f });
			if (pos.x >= maxPos_.x)
				switchFg_ = true;
		}
		if (pos.x >= minPos_.x && switchFg_ == true)
		{
			velocityComponent_->SetVelocity	   ({ -2.0f, 0.0f, 0.0f });
			if (pos.x <= minPos_.x)
				switchFg_ = false;
		}
		break;
	default:
		break;
	}
	this->transform_component_->SetPosition(pos);
}
//--------------------------------------------------
// @brief ���t�g�ɔC�ӂ̃I�u�W�F�N�g�������������̏���
//--------------------------------------------------
void Lift::OnCollisionEnter(GameObject* _other)
{
	std::cout << std::format("��Lift�� -> �Ȃ񂩂�������\n");
}
