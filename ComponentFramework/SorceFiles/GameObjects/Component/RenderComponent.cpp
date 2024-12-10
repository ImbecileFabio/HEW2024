//==================================================
// [RenderComponent.cpp] �`�惂�W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`�揈���̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "RenderComponent.h"
#include "../Component.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::cout << std::format("��RenderComponent�� -> Constructor\n");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << std::format("��RenderComponent�� -> Destructor\n");

}
