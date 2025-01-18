//==================================================
// [LiftComponent.cpp] ���t�g�R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�̋����𐧌䂷��R���|�[�l���g
//==================================================
/*----- �C���N���[�h -----*/


#include "../../GameObject.h"
#include "../../GameObject/Pendulum.h"



#include "LiftComponent.h"
#include "../TransformComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../PendulumMovementComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
LiftComponent::LiftComponent(GameObject* _owner, Pendulum* _pendulum, LiftComMoveState _moveState, int _updateOrder)
	:Component(_owner, _updateOrder)
	, lift_com_state_(LiftComState::Stop)
	, lift_com_move_state_(_moveState)
	, pendulum_(_pendulum)
	, max_move_distance_(0.0f)
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();

	start_pos_ = owner_transform_->GetPosition();
	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
LiftComponent::~LiftComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void LiftComponent::Init()
{
	max_move_distance_ = 0.0f;
	traveled_distance_ = { 0.0f, 0.0f };
	lift_com_state_ = LiftComState::Stop;
	this->InitDirection();
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void LiftComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void LiftComponent::Update()
{
	if (!pendulum_) return;

	switch (lift_com_state_)
	{
	case LiftComState::Stop:
	{
		owner_velocity_->SetVelocity({ 0.0f, 0.0f, 0.0f });
		break;
	}
	case LiftComponent::LiftComState::Move:
	{
		DirectX::SimpleMath::Vector3 liftPos = owner_transform_->GetPosition();
	
		auto moveSpeed = direction_ * owner_velocity_->GetSpeedRate();
		switch (lift_com_move_state_)
		{
		case LiftComponent::LiftComMoveState::length:	// �c�ړ�
		{
			// �ړ�������ݐ�
			traveled_distance_.y += std::abs(moveSpeed.y);
			break;
		}
		case LiftComponent::LiftComMoveState::side:		// ���ړ�
		{
			// �ړ�������ݐ�
			traveled_distance_.x += std::abs(moveSpeed.x);
			break;
		}
		case LiftComponent::LiftComMoveState::diagonalRight:	// �΂߈ړ��i�E�j
		case LiftComponent::LiftComMoveState::diagonalLeft:	// �΂߈ړ��i���j
		{
			// �ړ�������ݐ�
			Vector2 normalizedDirection = {
				direction_.x / std::sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y),
				direction_.y / std::sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y)
			};
			traveled_distance_.x += std::abs(normalizedDirection.x);
			traveled_distance_.y += std::abs(normalizedDirection.y);
			break;
		}
		default:
			break;
		}
		// ���t�g�̍��W���x�_�Ƃ��ēn��������
		owner_velocity_->SetVelocity(Vector3(moveSpeed.x, moveSpeed.y, 0.0f));
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	}

}

//--------------------------------------------------
// @brief ���t�g�̍ő�ړ�������ݒ�
// @return �ړ��������ő勗���𒴂��Ă���: true, �����Ă��Ȃ�: false
//--------------------------------------------------
bool LiftComponent::CheckTraveledDistance()
{
	bool switchFlg{};
	// �ړ������ŏ�����ς��Ă܂�
	if (lift_com_move_state_ == LiftComMoveState::length || lift_com_move_state_ == LiftComMoveState::side)
		switchFlg = CheckLengthSideTraveled();	// �c���ړ��̏ꍇ
	else
		switchFlg = CheckDiagonalTraveled();		// �΂߈ړ��̏ꍇ

	// �ړ��������ő�ړ������𒴂�����
	if (switchFlg)
	{
		direction_ = -direction_;	// �ړ������𔽓]
		traveled_distance_ = { 0.0f, 0.0f };	// �ړ����������Z�b�g
	}

	return switchFlg;
}

bool LiftComponent::CheckLengthSideTraveled()
{
	// �ړ��������ő�ړ������𒴂�����
	if (traveled_distance_.x >= max_move_distance_ && traveled_distance_.y >= max_move_distance_)
	{
		return true;
	}

	return false;
}

//--------------------------------------------------
// @brief ���t�g�̈ړ��������ő勗���𒴂��Ă��邩
// @return : �͂�: true, ������: false
//--------------------------------------------------
bool LiftComponent::CheckDiagonalTraveled()
{
	// �ړ��������ő�ړ������𒴂�����
	if (traveled_distance_.x >= max_move_distance_ || traveled_distance_.y >= max_move_distance_)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------
// @brief �ړ������̏�����
//--------------------------------------------------
void LiftComponent::InitDirection() {

	switch (lift_com_move_state_) {
	case LiftComponent::LiftComMoveState::length: // �c�ړ�
		direction_ = { 0.0f, 1.0f }; // �����
		break;
	case LiftComponent::LiftComMoveState::side: // ���ړ�
		direction_ = { 1.0f, 0.0f }; // �E����
		break;
	case LiftComponent::LiftComMoveState::diagonalRight: // �΂߉E�ړ�
		direction_ = { 1.0f, 1.0f }; // �E�����
		break;
	case LiftComponent::LiftComMoveState::diagonalLeft: // �΂ߍ��ړ�
		direction_ = { -1.0f, 1.0f }; // �������
		break;
	default:
		direction_ = { 0.0f, 0.0f }; // �Î~
		break;
	}
}