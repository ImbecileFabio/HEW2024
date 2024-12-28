#include "LiftComponent.h"
#include "../GameObject/Pendulum.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
LiftComponent::LiftComponent(Pendulum* _pendulum, MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameObject* _owner, int _updateOrder)
	:Component	(_owner, _updateOrder)
	, maxPos_	(_maxPos)	// �������̍ő���W
	, minPos_	(_minPos)	// �������̍ő���W
	, pendulum_	(_pendulum)	// ���t�g�̓����ƘA��������U��q�̎Q��
	, switchFg_	(false)		// �X�C�b�`�t���O
	, moveState_(_moveState)// �ړ����
{
	this->Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
LiftComponent::~LiftComponent(void)
{
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void LiftComponent::Init()
{
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void LiftComponent::Update()
{
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	auto velocity = owner_ ->GetComponent<VelocityComponent>();
	if (!velocity)
	{
		std::cout << std::format("[LiftComponent]-> �R���|�[�l���g���擾�ł��܂���ł���\n");
		return;
	}
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = owner_->GetTransformComponent()->GetPosition();

		switch (moveState_)
		{
		case LiftComponent::MoveState::length:	// �c�ړ�
			if (!switchFg_)
			{
				velocity->SetVelocity({ 0.0f, 2.0f, 0.0f });
				if (liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else
			{
				velocity->SetVelocity({ 0.0f, -2.0f, 0.0f });
				if (liftPos.y <= minPos_.y)
				{
					switchFg_ = false;
				}
			}
			break;
		case LiftComponent::MoveState::side:		// ���ړ�
			if (!switchFg_)
			{
				velocity->SetVelocity({ 2.0f, 0.0f, 0.0f });
				if (liftPos.x >= maxPos_.x)
				{
					switchFg_ = true;
				}
			}
			else
			{
				velocity->SetVelocity({ -2.0f, 0.0f, 0.0f });
				if (liftPos.x <= minPos_.x)
				{
					switchFg_ = false;
				}
			}
			break;
		case LiftComponent::MoveState::diagonal:	// �΂߈ړ�
			if (!switchFg_)
			{
				velocity->SetVelocity({ 2.0f, 2.0f, 0.0f });
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else {
				velocity->SetVelocity({ -2.0f, -2.0f, 0.0f });
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
				{
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// ���t�g�̍��W���x�_�Ƃ��ēn��������
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocity->SetVelocity({ 0.0f, 0.0f, 0.0f });
	}
}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void LiftComponent::Uninit()
{
}
