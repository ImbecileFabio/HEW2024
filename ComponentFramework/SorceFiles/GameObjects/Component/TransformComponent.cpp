//==================================================
// [TransformComponent.cpp] �p������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�p������R���|�[�l���g
//==================================================

/*----- �C���N���[�h -----*/
#include "../GameObject.h"
#include "../Component.h"
#include "TransformComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
TransformComponent::TransformComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	SetPosition(DirectX::SimpleMath::Vector3::Zero);
	SetRotation(DirectX::SimpleMath::Vector3::Zero);
	SetScale(DirectX::SimpleMath::Vector3::One);

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
TransformComponent::~TransformComponent()
{
	std::cout << "��TransformComponent�� -> �j��\n";

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

