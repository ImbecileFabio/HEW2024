//==================================================
// [LiftInteractionComponent.cpp]���t�g�C���^���N�V�����R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���t�g�ɐG���ƃR���|�[�l���g�̏��L�҂ɓ�����`���鏈��
//==================================================
/*----- �C���N���[�h -----*/
#include <SimpleMath.h>

#include "LiftInteractionComponent.h"

#include "../../GameObject/Lift.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
LiftInteractionComponent::LiftInteractionComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
LiftInteractionComponent::~LiftInteractionComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void LiftInteractionComponent::Init()
{
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void LiftInteractionComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void LiftInteractionComponent::Update()
{
	// ���t�g�����݂���ꍇ
	if (current_lift_) {
		// �����Ă���ꍇ
		if(current_lift_->GetLiftState() == Lift::LiftState::Move)
		{
			// ���t�g�̑��x�Ƒ��x�{�����擾���A���L�҂ɐݒ�
			auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();
			owner_->GetComponent<VelocityComponent>()->SetVelocity(liftVelocity->GetVelocity());
			owner_->GetComponent<VelocityComponent>()->SetSpeedRate(liftVelocity->GetSpeedRate());
		}
		// ��~���Ă���ꍇ
		else if(current_lift_->GetLiftState() == Lift::LiftState::Stop) {
			// ���t�g�̎Q�Ƃ�؂�
			current_lift_ = nullptr;
		}

	}
}

void LiftInteractionComponent::SetLift(Lift* _lift)
{
	if (current_lift_ == _lift) return;

	current_lift_ = _lift;

}
