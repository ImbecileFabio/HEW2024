//==================================================
// [PendulumMovementComponent.cpp] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//==================================================

#include "PendulumMovementComponent.h"
#include "../../PemdulumManager.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
PendulumMovementComponent::PendulumMovementComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder) {
	std::cout << std::format("��PendulumMovementComponent�� -> Constructor\n");

	Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
PendulumMovementComponent::~PendulumMovementComponent() {
	std::cout << std::format("��PendulumMovementComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void PendulumMovementComponent::Init() {
	pemdulumPosition_ = {};		// -�ʒu
	isPendulumAngle_ = 0;		// -���݂̐U��q�̊p�x
	wasPendulumAngle_ = 0;		// -���O�̐U��q�̊p�x
	isPendulumVelocity_ = 0;	// -���݂̊p���x
	wasPendulumVelocity_ = 0;	// -���O�̊p���x
	pendulumAcceleration_ = 0;	// -�U��q�̊p�����x
	fulcrumPosition_ = {};		// -�x�_�̍��W
	pendulumLength_ = 0;		// -�U��q�̒���
	pendulumRadian_ = 0;		// -�U��q�̊p�x�i���W�A���j
	turnPendulum_ = true;		// -�U��q�̉����ŏ�����؂�ւ��邽�߂̃t���O�@true�F�E���獶�@false�F������E

	langthState_= LangthState::normalLangth;
	pemdulumMovement_ = true;
	pemdulumSelected_ = false;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void PendulumMovementComponent::Update() {
	 //����m�F�p���O
	//std::cout << std::format("{}  ���݂̊p�x�F{}	�p���x�F{}\n", turnPendulum_, isPendulumAngle_, isPendulumVelocity_);
	
	// �U��q�̏�ԑJ��
	switch (langthState_)
	{
	case LangthState::shortLangth:
		SetPendulumLength(normalLangth - langthChange);
		break;
	case LangthState::normalLangth:
		SetPendulumLength(normalLangth);
		break;
	case LangthState::longLangth:
		SetPendulumLength(normalLangth + langthChange);
		break;
	default:
		break;
	}

	if (pemdulumMovement_ && GetPendulumAngle() == 0) { StartPemdulumMovement(); }

	PendulumAcceleration(pendulumAcceleration);				// �p�����x��ݒ�, �p���x��K�p
	PendulumPosition(fulcrumPosition_, pendulumLength_);	// ���W���v�Z
}


//--------------------------------------------------
// �U��q�̍��W���v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	if (isPendulumAngle_ > 0) {		// -�p�x�����̏ꍇ
		ConversionRadian(isPendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);

	}
	else if (isPendulumAngle_ < 0) {	// -�p�x�����̏ꍇ
		ConversionRadian(-isPendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x - _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	}
	else {					// -�p�x��0�̏ꍇ
		pemdulumPosition_.x = 0;
		pemdulumPosition_.y = _fulcrum.y - _length;
	}
	
	this->owner_->GetComponent<TransformComponent>()->SetPosition(pemdulumPosition_);
	this->owner_->GetComponent<TransformComponent>()->SetRotation(-isPendulumAngle_);
}

//--------------------------------------------------
// �U��q�̊p�x�̐��ڂ��v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumAcceleration(float _angularAcceleration) {
	if (turnPendulum_) {
		if (isPendulumAngle_ > 0) {
			SetPendulumAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			if (isPendulumAngle_ <= 0) {	// -�p�x��0���ׂ��ł��܂�����
				SetPendulumAngle(-wasPendulumAngle_);
				if (!pemdulumMovement_) { StopPemdulumMovement(); }
			}
		}
		else if(isPendulumAngle_ < 0) {
			SetPendulumAcceleration(_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (GetPemdulumVelocity() >= 0) {
				turnPendulum_ = false;
			}
		}
	} else {
		if (isPendulumAngle_ < 0) {
			SetPendulumAcceleration( _angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			if (isPendulumAngle_ >= 0) {	// -�p�x��0���ׂ��ł��܂�����
				SetPendulumAngle(-wasPendulumAngle_);
				if (!pemdulumMovement_) { StopPemdulumMovement(); }
			}
		}
		else if(isPendulumAngle_ > 0) {
			SetPendulumAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (GetPemdulumVelocity() <= 0) {
				turnPendulum_ = true;
			}
		}
	}
}

//--------------------------------------------------
// �U��q�̊p�x�Ɋp���x��K�p
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	SetPemdulumVelocity(std::round((GetPemdulumVelocity() + GetPendulumAcceleration()) * 1000) / 1000);
	SetPendulumAngle(std::round((GetPendulumAngle() + GetPemdulumVelocity()) * 1000) / 1000);
}

//--------------------------------------------------
// �p�x�����W�A���ɕϊ�
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}

//--------------------------------------------------
// �U��q�̏����l�ݒ�
//--------------------------------------------------
void PendulumMovementComponent::PendulumInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _pendulumAngle) {
	fulcrumPosition_ = _fulcrum;
	pemdulumMovement_ = _movement;
	maxPendulumAngle_ = _pendulumAngle;
	SetPendulumAngle(_pendulumAngle);
}

//--------------------------------------------------
// �U��q�̊p�x�̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumAngle(float _pendulumAngle) {
	wasPendulumAngle_ = isPendulumAngle_;
	isPendulumAngle_ = _pendulumAngle;
}
float PendulumMovementComponent::GetPendulumAngle() {
	return isPendulumAngle_;
}

//--------------------------------------------------
// �U��q�̊p���x�̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPemdulumVelocity(float _angularVelocity) {
	wasPendulumVelocity_ = isPendulumVelocity_;
	isPendulumVelocity_ = _angularVelocity;
}
float PendulumMovementComponent::GetPemdulumVelocity() {
	return isPendulumVelocity_;
}

//--------------------------------------------------
// �U��q�̊p�����x�̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumAcceleration(float _pendulumAcceleration) {
	pendulumAcceleration_ = _pendulumAcceleration;
}
float PendulumMovementComponent::GetPendulumAcceleration() {
	return pendulumAcceleration_;
}

//--------------------------------------------------
// �x�_�̍��W�̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPemdulumFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition) {
	fulcrumPosition_ = _fulcrumPosition;
}
DirectX::SimpleMath::Vector3 PendulumMovementComponent::GetPemdulumFulcrum() {
	return fulcrumPosition_;
}

//--------------------------------------------------
// �x���̒����̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumLength(float _pendulumLength) {
	pendulumLength_ = _pendulumLength;
}
float PendulumMovementComponent::GetPendulumLength() {
	return pendulumLength_;
}

//--------------------------------------------------
// �U��q�̒�~�A�n��
//--------------------------------------------------
void PendulumMovementComponent::StartPemdulumMovement() {
	for (int i = 1;;i++) {
		maxPemdulumVelocity_ += pendulumAcceleration * i;
		if (maxPemdulumVelocity_ >= maxPendulumAngle_) {
			SetPemdulumVelocity(pendulumAcceleration * i);
			break;
		}
	}
}
void PendulumMovementComponent::StopPemdulumMovement() {
	SetPendulumAngle(0);
	SetPemdulumVelocity(0);
	SetPendulumAcceleration(0);
}