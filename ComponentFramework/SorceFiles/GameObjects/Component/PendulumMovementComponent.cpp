//==================================================
// [PendulumMovementComponent.cpp] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//==================================================

#include "PendulumMovementComponent.h"
#include "../../PemdulumManager.h"
#include "../../AudioManager.h"

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
	pendulumPosition_ = {};		// -�ʒu
	isPendulumAngle_ = 0;		// -���݂̐U��q�̊p�x
	wasPendulumAngle_ = 0;		// -���O�̐U��q�̊p�x
	isPendulumVelocity_ = 0;	// -���݂̊p���x
	wasPendulumVelocity_ = 0;	// -���O�̊p���x
	pendulumAcceleration_ = 0;	// -�U��q�̊p�����x
	fulcrumPosition_ = {};		// -�x�_�̍��W
	pendulumLength_ = 0;		// -�U��q�̒���
	pendulumRadian_ = 0;		// -�U��q�̊p�x�i���W�A���j
	turnPendulum_ = true;		// -�U��q�̉����ŏ�����؂�ւ��邽�߂̃t���O�@true�F�E���獶�@false�F������E

	langthState_ = LangthState::normalLangth;
	pendulumMovement_ = false;
	pendulumSelected_ = false;
	pendulumDirection_ = 1;
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

	if (pendulumMovement_ && GetPendulumAngle() == 0.0f) 
	{ 
		StartPendulumMovement();
		PendulumVelocity();
	}

	PendulumAcceleration(pendulumAcceleration);				// �p�����x��ݒ�, �p���x��K�p
	PendulumPosition(fulcrumPosition_, pendulumLength_);	// ���W���v�Z
}


//--------------------------------------------------
// �U��q�̍��W���v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {

	//if (isPendulumAngle_ > 0) {		// -�p�x�����̏ꍇ
	//	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	//	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	//}
	//else if (isPendulumAngle_ < 0) {	// -�p�x�����̏ꍇ
	//	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	//	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	//}
	//else {					// -�p�x��0�̏ꍇ
	//	pendulumPosition_.x = _fulcrum.x;
	//	pendulumPosition_.y = _fulcrum.y - _length;
	//}

	// �U��q�̊p�x�̌v�Z���C�����Ă݂܂��� by arima
	// ��肪�Ȃ���Ώ�̃R�[�h�������Ƃ��Ă��������B
	// �p�x��0�x�t�߂̎��Ɂu�K�N�b�v���Ƃ��銴�G������̂ŗv�C�������B

	ConversionRadian(isPendulumAngle_);

	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	
	this->owner_->GetTransformComponent()->SetPosition(pendulumPosition_);
	this->owner_->GetTransformComponent()->SetRotation(-pendulumRadian_);
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
				if (!pendulumMovement_) { StopPendulumMovement(); }
			}
		}
		else if(isPendulumAngle_ < 0) {
			SetPendulumAcceleration(_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (GetPendulumVelocity() >= 0) {
				turnPendulum_ = false;
			}
		}
	} else {
		if (isPendulumAngle_ < 0) {
			SetPendulumAcceleration( _angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			if (isPendulumAngle_ >= 0) {	// -�p�x��0���ׂ��ł��܂�����
				SetPendulumAngle(-wasPendulumAngle_);
				if (!pendulumMovement_) { StopPendulumMovement(); }
			}
		}
		else if(isPendulumAngle_ > 0) {
			SetPendulumAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (GetPendulumVelocity() <= 0) {
				turnPendulum_ = true;
			}
		}
	}
}

//--------------------------------------------------
// �U��q�̊p�x�Ɋp���x��K�p
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	SetPendulumVelocity(std::round((GetPendulumVelocity() + GetPendulumAcceleration()) * 1000) / 1000);
	SetPendulumAngle(std::round((GetPendulumAngle() + GetPendulumVelocity()) * 1000) / 1000);
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
	pendulumMovement_ = _movement;
	maxPendulumAngle_ = _pendulumAngle;
	SetPendulumAngle(0.0f);
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
void PendulumMovementComponent::SetPendulumVelocity(float _angularVelocity) {
	wasPendulumVelocity_ = isPendulumVelocity_;
	isPendulumVelocity_ = _angularVelocity;
}
float PendulumMovementComponent::GetPendulumVelocity() {
	return isPendulumVelocity_;
}

//--------------------------------------------------
// �U��q�̒�~�A�n��
//--------------------------------------------------
void PendulumMovementComponent::StartPendulumMovement() {
	AudioManager::GetInstance()->Play(SoundLabel_HitSE);
	maxPendulumVelocity_ = 0;
	for (int i = 1;;i++) {
		maxPendulumVelocity_ += pendulumAcceleration * i;
		if (maxPendulumVelocity_ >= maxPendulumAngle_) {
			SetPendulumVelocity((pendulumAcceleration * i) * pendulumDirection_);
			break;
		}
	}
}
void PendulumMovementComponent::StopPendulumMovement() {
	SetPendulumAngle(0);
	SetPendulumVelocity(0);
	SetPendulumAcceleration(0);
}