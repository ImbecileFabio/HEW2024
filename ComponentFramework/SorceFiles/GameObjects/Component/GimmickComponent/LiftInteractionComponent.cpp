//==================================================
// [LiftInteractionComponent.cpp] HOGE�R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����FHOGE�R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
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
			auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();
			owner_->GetComponent<VelocityComponent>()->SetVelocity(liftVelocity->GetVelocity());
		}
		// ��~���Ă���ꍇ
		else if(current_lift_->GetLiftState() == Lift::LiftState::Stop) {
			// ���t�g�̎Q�Ƃ�؂�
			current_lift_ = nullptr;
		}

	}
}
