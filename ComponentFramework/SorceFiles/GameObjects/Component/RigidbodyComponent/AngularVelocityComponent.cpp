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

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void AngularVelocityComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void AngularVelocityComponent::Updata() {
	//UpdateVelocity();
}