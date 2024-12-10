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

	Init();
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
	// �g�p�t���O��true�Ȃ��p����
	use_acceleration_	= true;
	use_velocity_		= true;
	use_gravity_		= true;
	acceleration_	= { 0.f,0.f,0.f };
	velocity_		= { 0.f,0.f,0.f };
	gravity_		= { 0.f,-1.f,0.f };	// �ꉞ�Œ�
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void VelocityComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void VelocityComponent::Update(float _speed) {
	position_ = this->owner_->GetComponent<TransformComponent>()->GetPosition();	// -���ݍ��W�̎擾

	// ���x��K�p
	if (use_velocity_) {
		// �����x��K�p
		if (use_acceleration_) {
			velocity_ += acceleration_;
		}
		// �d�͂�K�p
		if (use_gravity_) {
			velocity_ += gravity_;
		}
		position_ += (velocity_ * _speed);
	}

	this->owner_->GetComponent<TransformComponent>()->SetPosition(position_);
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