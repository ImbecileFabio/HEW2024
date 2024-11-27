//==================================================
// [RigidbodyComponent.cpp] �������Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//==================================================

#include "RigidbodyComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RigidbodyComponent::RigidbodyComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder){
	std::cout << std::format("��RigidbodyComponent�� -> Constructor\n");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RigidbodyComponent::~RigidbodyComponent(){
	std::cout << std::format("��RigidbodyComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void RigidbodyComponent::Init(){

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void RigidbodyComponent::Uninit(){

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void RigidbodyComponent::Updata() {
	//UpdateVelocity();
}


////--------------------------------------------------
//// �����x
////--------------------------------------------------
//void	RigidbodyComponent::SetAcceleration(const Vector3 _acceleration) {
//	acceleration_ = _acceleration;
//}
//Vector3 RigidbodyComponent::GetAcceleration() const {
//	return acceleration_;
//}
//// -�g�p�t���O
//void	RigidbodyComponent::SetUseAcceleration(const bool _use_acceleration) {
//	use_acceleration_ = _use_acceleration;
//}
//bool	RigidbodyComponent::GetUseAcceleration() const {
//	return use_acceleration_;
//}
//
//
////--------------------------------------------------
//// ���x
////--------------------------------------------------
//void	RigidbodyComponent::SetVelocity(const Vector3 _velocity){
//	velocity_ = _velocity;
//}
//void	RigidbodyComponent::UpdateVelocity() {
//	position_ = owner_->GetTransformComponent()->GetPosition();	// -���ݍ��W�̎擾
//
//	// �����x��K�p
//	if (use_acceleration_) {	
//		velocity_.x += acceleration_.x;
//		velocity_.y += acceleration_.y;
//		velocity_.z += acceleration_.z;
//	}
//	// �d�͂�K�p�i�ꉞ�O�Ƃ��j
//	if (use_gravity_) {
//		velocity_.x += gravity_.x;
//		velocity_.y += gravity_.y;
//		velocity_.z += gravity_.z;
//	}
//
//	position_.x += velocity_.x;
//	position_.y += velocity_.y;
//	position_.z += velocity_.z;
//
//	owner_->GetTransformComponent()->SetPosition(velocity_);
//}
//Vector3	RigidbodyComponent::GetVelocity() const {
//	return velocity_;
//}
//// -�g�p�t���O
//void	RigidbodyComponent::SetUseVelocity(const bool _use_velocity) {
//	use_velocity_ = _use_velocity;
//}
//bool	RigidbodyComponent::GetUseVelocity() const {
//	return use_velocity_;
//}
//
//
////--------------------------------------------------
//// �d��
////--------------------------------------------------
//// -�g�p�t���O
//void	RigidbodyComponent::SetUseGravity(const bool _use_gravity) {
//	use_gravity_ = _use_gravity;
//}
//bool	RigidbodyComponent::GetUseGravity() const {
//	return use_gravity_;
//}