//==================================================
// [PendulumComponent.cpp] �U��q���W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̏����̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <SimpleMath.h>


#include "PendulumComponent.h"
#include "../GameObject.h"
#include "../Component.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
PendulumComponent::PendulumComponent(GameObject* _owner, float _rength, float _angle, int _updateOrder)
	: Component(_owner, _updateOrder)
	, rength_(_rength)
	, angle_(_angle)
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


//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void PendulumComponent::Update(void)
{

	auto& transform = owner_->GetTransformComponent();

	transform->position_.y = -rength_;
	transform->rotation_.z += 0.1f;
}