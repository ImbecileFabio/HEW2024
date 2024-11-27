//==================================================
// [AngularVelocityComponent.cpp] �p���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�S�D�p���x�A��]
//==================================================

#include "AngularVelocityComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
AngularVelocityComponent::AngularVelocityComponent(GameObject* _owner, int _updateOrder)
	:RigidbodyComponent(_owner, _updateOrder) {
	std::cout << std::format("��AngularVelocityComponent�� -> Constructor\n");

	Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
AngularVelocityComponent::~AngularVelocityComponent() {
	std::cout << std::format("��AngularVelocityComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void AngularVelocityComponent::Init() {
	use_angularAcceleration_	= true;
	use_angularVelocity_		= true;
	angularAcceleration_	= 0.f;
	angularVelocity_		= 0.f;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void AngularVelocityComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void AngularVelocityComponent::Update() {
	rotation_ = this->owner_->GetComponent<TransformComponent>()->GetRotation().z;	// -���ݍ��W�̎擾

	// �p�����x��K�p
	if (use_angularVelocity_) {
		// �p���x��K�p
		if (use_angularAcceleration_) {
			angularVelocity_ += angularAcceleration_;
		}

		rotation_ += angularVelocity_;
	}

	this->owner_->GetComponent<TransformComponent>()->SetRotation(rotation_);
}


//--------------------------------------------------
//�p�����x
//--------------------------------------------------
void	AngularVelocityComponent::SetAngularAcceleration(const float _angularAcceleration) {
	angularAcceleration_ = _angularAcceleration;
}
float AngularVelocityComponent::GetAngularAcceleration() const {
	return angularAcceleration_;
}
void	AngularVelocityComponent::SetUseAngularAcceleration(const bool _use_angularAcceleration) {
	use_angularAcceleration_ = _use_angularAcceleration;
}
bool	AngularVelocityComponent::GetUseAngularAcceleration() const {
	return use_angularAcceleration_;
}

//--------------------------------------------------
//�p���x
//--------------------------------------------------
void	AngularVelocityComponent::SetAngularVelocity(const float _angularVelocity) {
	angularVelocity_ = _angularVelocity;
}
float AngularVelocityComponent::GetAngularVelocity() const {
	return angularVelocity_;
}
void	AngularVelocityComponent::SetUseAngularVelocity(const bool _use_angularVelocity) {
	use_angularVelocity_ = _use_angularVelocity;
}
bool	AngularVelocityComponent::GetUseAngularVelocity() const {
	return use_angularVelocity_;
}