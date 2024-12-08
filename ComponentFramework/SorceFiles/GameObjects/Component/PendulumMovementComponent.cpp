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
	angle_ = -(this->owner_->GetComponent<TransformComponent>()->GetRotation().z);
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
void PendulumMovementComponent::Update() {
	
}


//--------------------------------------------------
// �U��q�̍��W���v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	angle_ = -(this->owner_->GetComponent<TransformComponent>()->GetRotation().z);

	if (angle_ > 0) {		// -�p�x�����̏ꍇ
		ConversionRadian(angle_);
		pemdulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);

	}
	else if (angle_ < 0) {	// -�p�x�����̏ꍇ
		ConversionRadian(-angle_);
		pemdulumPosition_.x = _fulcrum.x - _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	}
	else {					// -�p�x��0�̏ꍇ
		pemdulumPosition_.x = 0;
		pemdulumPosition_.y = _fulcrum.y - _length;
	}
	
	this->owner_->GetComponent<TransformComponent>()->SetPosition(pemdulumPosition_);
}

//--------------------------------------------------
// �U��q�̊p�x�̐��ڂ��v�Z
//--------------------------------------------------
void PendulumMovementComponent::PendulumAngle(float _angularAcceleration) {
	if (angle_ > 0) {			// -���̊p�x�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
	} else if (angle_ < 0) {	// -���̊p�x�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
	} else {					// -�p�x��0�̏ꍇ
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(0.f);
	}
}

//--------------------------------------------------
// �p�x�����W�A���ɕϊ�
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}