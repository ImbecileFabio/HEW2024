//==================================================
// [VelocityComponent.cpp] ���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F���x���Z�������Ȃ��N���X
//		�P�D�ʒu�A���x
//		�Q�D�d��
//==================================================

#include "VelocityComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
VelocityComponent::VelocityComponent(GameObject* _owner, int _updateOrder)
	:RigidbodyComponent(_owner, _updateOrder) {
	std::cout << std::format("��VelocityComponent�� -> Constructor\n");

	// �g�p�t���O��true�Ȃ��p����
	use_acceleration_	= true;
	use_velocity_		= true;
	use_gravity_		= true;
	gravity_ = { 0.0f,-1.0f,0.0f };	// �ꉞ�Œ�
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
VelocityComponent::~VelocityComponent() {
	std::cout << std::format("��VelocityComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void VelocityComponent::Init() {

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void VelocityComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void VelocityComponent::Updata() {
	position_ = owner_->GetTransformComponent()->GetPosition();	// -���ݍ��W�̎擾

	// �����x��K�p
	if (use_acceleration_) {
		velocity_.x += acceleration_.x;
		velocity_.y += acceleration_.y;
		velocity_.z += acceleration_.z;
	}
	// �d�͂�K�p�i�ꉞ�O�Ƃ��j
	if (use_gravity_) {
		velocity_.x += gravity_.x;
		velocity_.y += gravity_.y;
		velocity_.z += gravity_.z;
	}

	position_.x += velocity_.x;
	position_.y += velocity_.y;
	position_.z += velocity_.z;

	owner_->GetTransformComponent()->SetPosition(velocity_);
}


//--------------------------------------------------
// �����x
//--------------------------------------------------
void	VelocityComponent::SetAcceleration(const DirectX::SimpleMath::Vector3 _acceleration) {
	acceleration_ = _acceleration;
}
DirectX::SimpleMath::Vector3 VelocityComponent::GetAcceleration() const {
	return acceleration_;
}
// -�g�p�t���O
void	VelocityComponent::SetUseAcceleration(const bool _use_acceleration) {
	use_acceleration_ = _use_acceleration;
}
bool	VelocityComponent::GetUseAcceleration() const {
	return use_acceleration_;
}


//--------------------------------------------------
// ���x
//--------------------------------------------------
void	VelocityComponent::SetVelocity(const DirectX::SimpleMath::Vector3 _velocity) {
	velocity_ = _velocity;
}
//void	VelocityComponent::UpdateVelocity() {
//
//}
DirectX::SimpleMath::Vector3	VelocityComponent::GetVelocity() const {
	return velocity_;
}
// -�g�p�t���O
void	VelocityComponent::SetUseVelocity(const bool _use_velocity) {
	use_velocity_ = _use_velocity;
}
bool	VelocityComponent::GetUseVelocity() const {
	return use_velocity_;
}


//--------------------------------------------------
// �d��
//--------------------------------------------------
// -�g�p�t���O
void	VelocityComponent::SetUseGravity(const bool _use_gravity) {
	use_gravity_ = _use_gravity;
}
bool	VelocityComponent::GetUseGravity() const {
	return use_gravity_;
}