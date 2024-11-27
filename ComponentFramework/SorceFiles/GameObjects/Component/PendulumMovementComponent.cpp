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

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void PendulumMovementComponent::Updata() {

}