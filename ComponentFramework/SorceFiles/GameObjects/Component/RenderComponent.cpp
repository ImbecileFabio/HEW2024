//==================================================
// [RenderComponent.cpp] �`�惂�W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`�揈���̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <format>

#include "RenderComponent.h"
#include "../Component.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::format("{}\n", "��RenderComponent�� -> Constructor");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::format("{}\n", "��RenderComponent�� -> Destructor");

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void RenderComponent::Uninit()
{
}
