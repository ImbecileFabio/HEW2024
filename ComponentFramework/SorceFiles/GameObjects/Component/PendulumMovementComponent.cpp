//==================================================
// [PendulumMovementComponent.cpp] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//==================================================

#include "PendulumMovementComponent.h"
#include "RigidbodyComponent/AngularVelocityComponent.h"

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
	isPendulumAngle_	= 0.f;
	wasPendulumAngle_	= 0.f;
	pendulumRadian_		= 0.f;
	turnPendulum_		= true;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void PendulumMovementComponent::Update(float _angle, DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	//std::cout << std::format("{}  {}  {}  {}  {}\n", turnPendulum_, isPendulumAngle_, wasPendulumAngle_,
	//	this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity(),
	//	this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularAcceleration());
	PendulumAcceleration(_angle);			// �p�����x��ݒ�, �p���x��K�p
	PendulumPosition(_fulcrum, _length);	// ���W���v�Z
	
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
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			if (isPendulumAngle_ <= 0) {	// -�p�x��0���ׂ��ł��܂�����
				isPendulumAngle_ = -wasPendulumAngle_;
			}
		}
		else {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() >= 0) {	
				turnPendulum_ = false;
			}
		}
	} else {
		if (isPendulumAngle_ < 0) {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			if (isPendulumAngle_ >= 0) {	// -�p�x��0���ׂ��ł��܂�����
				isPendulumAngle_ = -wasPendulumAngle_;
			}
		}
		else {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -�p���x��K�p 
			// �ō����B�_�Ɏ������甽�]
			if (this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() <= 0) {
				turnPendulum_ = true;
			}
		}
	}
	//if (isPendulumAngle_ > 0) {			// -���̊p�x�̏ꍇ
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
	//} else if (isPendulumAngle_ < 0) {	// -���̊p�x�̏ꍇ
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
	//} else {					// -�p�x��0�̏ꍇ
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(0.f);
	//}
}

//--------------------------------------------------
// �U��q�̊p�x�Ɋp���x��K�p
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	// �p���x�Ɋp�����x��K�p�����l���A�p���x�ɓ��͂���
	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularVelocity(
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() +
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularAcceleration());

	wasPendulumAngle_ = isPendulumAngle_;
	isPendulumAngle_ += this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity();
}

//--------------------------------------------------
// �p�x�����W�A���ɕϊ�
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}

//--------------------------------------------------
// �U��q�̊p�x�̃Z�b�^�[�Q�b�^�[
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumAngle(float _pendulumAngle) {
	if (_pendulumAngle > 0) {
		turnPendulum_ = true;
	} else {
		turnPendulum_ = false;
	}
	isPendulumAngle_ = _pendulumAngle;
}
float PendulumMovementComponent::GetPendulumAngle() {
	return isPendulumAngle_;
}