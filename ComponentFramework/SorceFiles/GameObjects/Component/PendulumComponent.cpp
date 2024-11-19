//==================================================
// [PendulumComponent.cpp] �U��q���W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̏����̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <format>

#include "PendulumComponent.h"
#include "../Component.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
PendulumComponent::PendulumComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::format("��PendulumComponent�� -> Constructor\n");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
PendulumComponent::~PendulumComponent(void)
{
	std::format("��PendulumComponent�� -> Destructor\n");

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void PendulumComponent::Uninit()
{
}
