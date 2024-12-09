//==================================================
// [Lift.cpp] ���t�g�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�I�u�W�F�N�g
//==================================================
/*----- �C���N���[�h -----*/
#include "Lift.h"
#include "../Component/LiftComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
// @param _maxPos �������̍ő���W
// @param _minPos �������̍ő���W
// @param _gameManager �I�u�W�F�N�g���������Ă���}�l�[�W���[
//--------------------------------------------------
Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager)
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
	delete spriteComponent_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	this->spriteComponent_   = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png", 0);

	this->transform_component_->SetScale(300.0f, 300.0f);
	this->transform_component_->SetPosition(0.0f, 0.0f);
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
		break;
	case Lift::MoveState::side:		// ���ړ�
		if (pos.x < maxPos_.x && switchFg_ == false)
		{
			pos.x += 2.0f;
			if (pos.x >= maxPos_.x)
			{
				switchFg_ = true;
			}
		}
		if (pos.x > minPos_.x && switchFg_ == true)
		{
			pos.x -= 2.0f;
			if (pos.x <= minPos_.x)
			{
				switchFg_ = false;
			}
		}
		break;
	default:
		break;
	}
	this->transform_component_->SetPosition(pos);
}
