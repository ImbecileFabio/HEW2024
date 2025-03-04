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
	// ���t�g�����݂��Ȃ��ꍇ
	if (!current_lift_) return;

	// �����Ă���ꍇ
	if (current_lift_->GetLiftState() == Lift::LiftState::Move)
	{

		auto ownerTransform = owner_->GetTransformComponent();
		auto ownerPos = ownerTransform->GetPosition();
		auto liftHitBox = current_lift_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
		auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();

		// Y���̈ʒu����
		float targetY = liftHitBox.max_.y + (ownerTransform->GetSize().y * 0.5f);

		const float smoothFactor = 0.15f;
		float newY = std::lerp(ownerPos.y, targetY, smoothFactor);

		// �ʒu�ύX
		ownerTransform->SetPosition(ownerPos.x, newY, ownerPos.z);


		// ���x�̓���
		auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
		if (ownerVelocity && liftVelocity)
		{
			Vector3 liftVel = liftVelocity->GetVelocity();
			ownerVelocity->SetVelocity(liftVel);
			ownerVelocity->SetSpeedRate(liftVelocity->GetSpeedRate());
		}
	}
	// ��~��Ԃ̏ꍇ
	else if (current_lift_->GetLiftState() == Lift::LiftState::Stop)
	{
		current_lift_ = nullptr;
	}
}

//--------------------------------------------------
// @param _lift: ���t�g
// @brief ���t�g���Z�b�g
//--------------------------------------------------
void LiftInteractionComponent::SetLift(Lift* _lift)
{
	if (!_lift || _lift->GetLiftState() == Lift::LiftState::Stop)
	{
		current_lift_ = nullptr;
		return;
	}

	// ���ɃZ�b�g����Ă��郊�t�g�Ɠ����Ȃ璎�ꍇ�͖���
	if (current_lift_ == _lift) return;


	// �O�̃��t�g�Ƃ̊֘A������
	if (current_lift_) {
		auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
		ownerVelocity->SetVelocity(Vector3::Zero);
	}

	// �V�������t�g���Z�b�g
	current_lift_ = _lift;

	// �������x���Z�b�g
	auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
	auto liftVelocity = _lift->GetComponent<VelocityComponent>();
	if (ownerVelocity && liftVelocity)
	{
		ownerVelocity->SetVelocity(liftVelocity->GetVelocity());
		ownerVelocity->SetSpeedRate(liftVelocity->GetSpeedRate());
	}
}


//--------------------------------------------------
// @param _lift: ���t�g
// @brief ���t�g�̒����ɐG��Ă��邩
// @return �G��Ă���: true, �G��Ă��Ȃ�: false
//--------------------------------------------------
bool LiftInteractionComponent::IsTouchingLiftCenter(Lift* _lift)
{
	if (!_lift) return false;

	// ���t�g�̒��S�ƕ����擾
	auto liftHitbox = _lift->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
	float liftCenter = (liftHitbox.max_.x + liftHitbox.min_.x) * 0.5f;
	float liftWidth = liftHitbox.max_.x - liftHitbox.min_.x;

	// �v���C���[�̃q�b�g�{�b�N�X���擾
	auto ownerPos = owner_->GetTransformComponent()->GetPosition();

	// �v���C���[�����t�g�̒��S�t�߂ɂ��邩�`�F�b�N
	float allowedOffset = liftWidth * 0.4f;  // ���t�g����40%�����e�͈͂Ƃ���
	return abs(ownerPos.x - liftCenter) < allowedOffset;
}
