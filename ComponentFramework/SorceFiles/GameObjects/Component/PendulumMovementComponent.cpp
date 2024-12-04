//==================================================
// [PendulumMovementComponent.cpp] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//==================================================

#include "PendulumMovementComponent.h"

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
	pendulumAngle_ = 0.f;
	pendulumRadian_ = 0.f;
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
	PendulumAcceleration(_angle);			// �p�����x��ݒ�
	PendulumVelocity();						// �p���x��K�p
	PendulumPosition(_fulcrum, _length);	// ���W���v�Z
}


//--------------------------------------------------
// �U��q�̍��W���v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	if (pendulumAngle_ > 0) {		// -�p�x�����̏ꍇ
		ConversionRadian(pendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);

	}
	else if (pendulumAngle_ < 0) {	// -�p�x�����̏ꍇ
		ConversionRadian(-pendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x - _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	}
	else {					// -�p�x��0�̏ꍇ
		pemdulumPosition_.x = 0;
		pemdulumPosition_.y = _fulcrum.y - _length;
	}
	
	this->owner_->GetComponent<TransformComponent>()->SetPosition(pemdulumPosition_);
	this->owner_->GetComponent<TransformComponent>()->SetRotation(-pendulumAngle_);
}

//--------------------------------------------------
// �U��q�̊p�x�̐��ڂ��v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumAcceleration(float _angularAcceleration) {
	if (pendulumAngle_ > 0) {			// -���̊p�x�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
	} else if (pendulumAngle_ < 0) {	// -���̊p�x�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
	} else {					// -�p�x��0�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(0.f);
	}
}

//--------------------------------------------------
// �U��q�̊p�x�Ɋp���x��K�p
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	// �p���x�Ɋp�����x��K�p�����l���A�p���x�ɓ��͂���
	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularVelocity(
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() +
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularAcceleration());

	pendulumAngle_ += this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity();
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
	pendulumAngle_ = _pendulumAngle;
}
float PendulumMovementComponent::GetPendulumAngle() {
	return pendulumAngle_;
}