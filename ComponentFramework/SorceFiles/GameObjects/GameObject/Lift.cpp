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
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Lift::~Lift()
{
	delete spriteComponent_;
	delete velocityComponent_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	this->spriteComponent_   = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png", 0);
	this->velocityComponent_ = new VelocityComponent(this);

	this->transform_component_->SetScale(300.0f, 300.0f);
	this->transform_component_->SetPosition(-50.0f, 0.0f);

	this->velocityComponent_->SetUseGravity(false);
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	DirectX::SimpleMath::Vector3 pos = this->transform_component_->GetPosition();
	DirectX::SimpleMath::Vector3 current_acceleration = velocityComponent_->GetAcceleration();

	switch (moveState_)
	{
	case Lift::MoveState::length:	// �c�ړ�
		break;
	case Lift::MoveState::side:		// ���ړ�
	{
		if (pos.x < maxPos_.x && switchFg_ == false)
		{
			velocityComponent_->SetAcceleration({ 0.1f, 0.0f, 0.0f });
			if (pos.x >= maxPos_.x)
				switchFg_ = true;
		}
		if (pos.x > minPos_.x && switchFg_ == true)
		{
			velocityComponent_->SetAcceleration({ -0.1f, 0.0f, 0.0f });
			if (pos.x <= minPos_.x)
				switchFg_ = false;
		}
		// �����x�̐�Βl���������Ɋ�Â��Č���������
		if (current_acceleration.x > 0.0f)
		{
			current_acceleration.x =
				max( 0.0f , current_acceleration.x - 0.01f );
		}
		else if (current_acceleration.x < 0.0f)
		{
			current_acceleration.x =
				min(0.0f , current_acceleration.x + 0.01f );
		}
		velocityComponent_->SetAcceleration(current_acceleration);
		break;
	}
	default:
		break;
	}
	this->transform_component_->SetPosition(pos);
}
//if (pos.x < maxPos_.x && switchFg_ == false)
//{
//	pos.x += 2.0f;
//	if (pos.x >= maxPos_.x)
//	{
//		switchFg_ = true;
//	}
//}
//if (pos.x > minPos_.x && switchFg_ == true)
//{
//	pos.x -= 2.0f;
//	if (pos.x <= minPos_.x)
//	{
//		switchFg_ = false;
//	}
//}