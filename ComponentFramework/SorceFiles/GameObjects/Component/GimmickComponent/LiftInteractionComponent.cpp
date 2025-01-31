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
#include "../../Component/ColliderComponent/BoxColliderComponent.h"

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
	if (!current_lift_) return;

	// �����Ă���ꍇ
	if (current_lift_->GetLiftState() == Lift::LiftState::Move)
	{
		auto ownerTransform = owner_->GetTransformComponent();
		auto ownerSize = ownerTransform->GetSize();
		auto ownerPos = ownerTransform->GetPosition();
		auto liftHitBox = current_lift_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();

		// y���̈ʒu��␳����
		auto newY = (liftHitBox.max_.y + ownerSize.y / 2) - 2.5f;
		ownerTransform->SetPosition(ownerPos.x, newY, ownerPos.z);

		// ���t�g�̑��x�Ƒ��x�{�����擾���A���L�҂ɐݒ�
		auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();
		owner_->GetComponent<VelocityComponent>()->SetVelocity(liftVelocity->GetVelocity());
		owner_->GetComponent<VelocityComponent>()->SetSpeedRate(liftVelocity->GetSpeedRate());
	}
	// ��~���Ă���ꍇ
	else if (current_lift_->GetLiftState() == Lift::LiftState::Stop) {
		// ���t�g�̎Q�Ƃ�؂�
		current_lift_ = nullptr;
	}

}

//--------------------------------------------------
// @param _lift: ���t�g
// @brief ���t�g���Z�b�g
//--------------------------------------------------
void LiftInteractionComponent::SetLift(Lift* _lift)
{
    if (current_lift_ == _lift) return;  // ���łɓ������t�g�Ȃ牽�����Ȃ�

    if (_lift->GetLiftState() == Lift::LiftState::Stop) return; // ��~���t�g�ɂ͏��Ȃ�

    // �܂�����Ă��Ȃ����A���������Ă���ꍇ�� `SetLift()` ����
	if (!current_lift_ || IsTouchingLiftCenter(_lift))
	{
		current_lift_ = _lift;
		owner_->GetComponent<VelocityComponent>()->SetVelocity(Vector3::Zero); // ���x���Z�b�g
	}
}


//--------------------------------------------------
// @param _lift: ���t�g
// @brief ���t�g�̒����ɐG��Ă��邩
// @return �G��Ă���: true, �G��Ă��Ȃ�: false
//--------------------------------------------------
bool LiftInteractionComponent::IsTouchingLiftCenter(Lift* _lift)
{
	// Lift�̒��S
	auto liftCenter = _lift->GetTransformComponent()->GetPosition().x;

	// owner��AABB
	auto ownerHitbox = owner_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();

	return (liftCenter > ownerHitbox.min_.x && liftCenter < ownerHitbox.max_.x);
}
