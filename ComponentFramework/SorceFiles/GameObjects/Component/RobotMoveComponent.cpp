//==================================================
// [RobotMoveComponent.cpp] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include "RobotMoveComponent.h"

#include "../GameObject.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(20.0f)
{

	this->Init();
}


//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RobotMoveComponent::~RobotMoveComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void RobotMoveComponent::Init()
{
	right_move_flg_ = true;	// �E�ړ�
	on_ground_flg_ = false;	// ��
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void RobotMoveComponent::Uninit()
{

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void RobotMoveComponent::Update()
{
	auto velocity = this->owner_->GetComponent<VelocityComponent>();
	auto collider = this->owner_->GetComponent<BoxColliderComponent>();
	auto transform = this->owner_->GetComponent<TransformComponent>();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> �R���|�[�l���g���擾�ł��܂���ł���\n");
		return; 
	}

	CheckTurnAround(*transform, *collider);

	if (right_move_flg_)
	{
		velocity->SetVelocity(Vector3(speed_, 0, 0));
	}
	else
	{
		velocity->SetVelocity(Vector3(-speed_, 0, 0));
	}

}


//--------------------------------------------------
// �n�ʂ̌��o����
//--------------------------------------------------
void RobotMoveComponent::CheckTurnAround(TransformComponent& _transform, BoxColliderComponent& _collider)
{
	// �n�ʂ̌��o����������\��
	
	auto pos = _transform.GetPosition();
	auto size = _collider.GetBoxSize();
	// ��ʊO�ɏo�����ɂȂ�Ȃ�
	if (pos.x < (-960 - size.x / 2))
	{
		right_move_flg_ = true;
	}
	else if (pos.x > (960 + size.x / 2))
	{
		right_move_flg_ = false;
	}
}