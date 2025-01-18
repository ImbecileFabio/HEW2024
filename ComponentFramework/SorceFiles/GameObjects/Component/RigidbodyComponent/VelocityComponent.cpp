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

	acceleration_	= { 0.0f, 0.0f, 0.0f };
	velocity_		= { 0.0f, 0.0f, 0.0f };
	speed_rate_ = 1.0f;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void VelocityComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void VelocityComponent::Update() {
	position_ = this->owner_->GetTransformComponent()->GetPosition();	// -���ݍ��W�̎擾

	// ���x��K�p
	if (use_velocity_) {
		// �����x��K�p
		if (use_acceleration_) {
			velocity_ += acceleration_;
		}
		position_ += (velocity_ * speed_rate_);
	}

	this->owner_->GetTransformComponent()->SetPosition(position_);

	std::cout << std::format("��VelocityComponent�� ->[{}] x : {}, y : {}\n", owner_->GetObjectName(), velocity_.x, velocity_.y);

}
//--------------------------------------------------
// ���x�W�����Z�b�g
//--------------------------------------------------
void VelocityComponent::SetSpeedRate(const float _speed_rate)
{
	speed_rate_ = _speed_rate;
}
//--------------------------------------------------
// ���x�W�����Q�b�g
//--------------------------------------------------
float VelocityComponent::GetSpeedRate(void)
{
	return speed_rate_;
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
