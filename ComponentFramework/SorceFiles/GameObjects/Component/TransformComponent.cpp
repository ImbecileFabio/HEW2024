//==================================================
// [TransformComponent.cpp] �p������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�p������R���|�[�l���g
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "TransformComponent.h"
#include "../GameObject.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
TransformComponent::TransformComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::cout << std::format("��TransformComponent�� -> Constructor\n");

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
TransformComponent::~TransformComponent()
{
	std::cout << std::format("��TransformComponent�� -> Destructor\n");

}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void TransformComponent::Init(void)
{
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void TransformComponent::Uninit(void)
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void TransformComponent::Update(void)
{

}

