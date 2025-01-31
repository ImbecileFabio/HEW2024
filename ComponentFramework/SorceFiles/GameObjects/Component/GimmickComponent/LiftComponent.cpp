//==================================================
// [LiftComponent.cpp] ���t�g�R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�̋����𐧌䂷��R���|�[�l���g
//==================================================
/*----- �C���N���[�h -----*/


#include "../../GameObject.h"
#include "../..//GameObject/Pendulum.h"

#include "../../../AudioManager.h"
#include "../../GameObject/Lift.h"

#include "LiftComponent.h"
#include "../TransformComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../PendulumMovementComponent.h"
#include "../../GameObject/Gimmick/Group/LiftGroup.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
LiftComponent::LiftComponent(GameObject* _owner, LiftComMoveState _moveState, Vector3 _startPos, Vector3 _endPos, Pendulum* _pendulum, int _updateOrder)
	:Component(_owner, _updateOrder)
	, lift_com_state_(LiftComState::Stop)
	, lift_com_move_state_(_moveState)
	, pendulum_(_pendulum)
	, start_pos_(_startPos)
	, end_pos_(_endPos)
	, turn_flg_(false)
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();

	float dx = end_pos_.x - start_pos_.x;
	float dy = end_pos_.y - start_pos_.y;
	max_move_distance_ = std::sqrt(dx * dx + dy * dy);

	// �ړ�����
	if (max_move_distance_ != 0.0f)
		direction_ = { dx / max_move_distance_, dy / max_move_distance_ };
	else
		direction_ = { 0.0f, 0.0f };

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
	traveled_distance_ = { 0.0f, 0.0f };
	lift_com_state_ = LiftComState::Stop;																															
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
		AudioManager::GetInstance()->Stop(this->GetOwner()->GetType(),this->GetOwner()->GetObjectFier());
		break;
	}
	case LiftComState::Wait:
	{
		owner_velocity_->SetVelocity({ 0.0f, 0.0f, 0.0f });
		break;
	}

	case LiftComponent::LiftComState::Move:
	{
		switch (lift_com_move_state_)
		{
		case LiftComponent::LiftComMoveState::length:	// �c�ړ�
		{
			// �ړ��ʂ��Z�b�g
			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
			// �ړ�������ݐ�
			traveled_distance_.y += std::abs(direction_.y) * owner_velocity_->GetSpeedRate();
			break;
		}
		case LiftComponent::LiftComMoveState::side:		// ���ړ�
		{
			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
			// �ړ�������ݐ�
			traveled_distance_.x += std::abs(direction_.x) * owner_velocity_->GetSpeedRate();
			break;
		}
		case LiftComponent::LiftComMoveState::diagonalRight:	// �΂߈ړ��i�E�j
		case LiftComponent::LiftComMoveState::diagonalLeft:	// �΂߈ړ��i���j
		{

			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));

			// ����������ݐ�
			auto stepDistance = std::sqrt(
				(direction_.x * owner_velocity_->GetSpeedRate()) * (direction_.x * owner_velocity_->GetSpeedRate()) +
				(direction_.y * owner_velocity_->GetSpeedRate()) * (direction_.y * owner_velocity_->GetSpeedRate())
			);

			traveled_distance_.x += stepDistance;
			traveled_distance_.y += stepDistance;
			break;
		}
		default:
			break;
		}

		if (!AudioManager::GetInstance()->GetPlayingState(this->GetOwner()->GetType(), this->GetOwner()->GetObjectFier()))
			AudioManager::GetInstance()->Play(this->GetOwner()->GetType(), this->GetOwner()->GetObjectFier());
	}
	}

		// ���t�g�̍��W���x�_�Ƃ��ēn��������
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(owner_transform_->GetPosition());
}

//--------------------------------------------------
// @brief ���t�g�̍ő�ړ�������ݒ�
// @return �ړ��������ő勗���𒴂��Ă���: true, �����Ă��Ȃ�: false
//--------------------------------------------------
bool LiftComponent::CheckTraveledDistance()
{
	bool switchFlg = false;
	// �ړ������ŏ�����ς��Ă܂�
	if (lift_com_move_state_ == LiftComMoveState::length || lift_com_move_state_ == LiftComMoveState::side)
		switchFlg = CheckLengthSideTraveled();	// �c���ړ��̏ꍇ
	else
		switchFlg = CheckDiagonalTraveled();		// �΂߈ړ��̏ꍇ

	// �ړ��������ő�ړ������𒴂�����
	if (switchFlg)
	{
		// ���W�̂�����Ȃ���
		if (turn_flg_)
		{
			owner_transform_->SetPosition(start_pos_);
		}
		else
		{
			owner_transform_->SetPosition(end_pos_);
		}

		turn_flg_ = !turn_flg_;	// ���̕␳�ʒu��؂�ւ���
		direction_ = -direction_;	// �ړ������𔽓]
		traveled_distance_ = { 0.0f, 0.0f };	// �ړ����������Z�b�g
	}

	return switchFlg;
}

bool LiftComponent::CheckLengthSideTraveled()
{
	// �ړ��������ő�ړ������𒴂�����
	if (traveled_distance_.x >= max_move_distance_ || traveled_distance_.y >= max_move_distance_)
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
	if (traveled_distance_.x >= max_move_distance_ && traveled_distance_.y >= max_move_distance_)
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