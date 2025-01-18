//==================================================
// [TimeZoneComponent.cpp] HOGE�R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����FHOGE�R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
#include "TimeZoneComponent.h"

#include "../GameObject.h"

#include "PendulumMovementComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
TimeZoneComponent::TimeZoneComponent(GameObject* _owner, GameObject* _ownerPendulum, int _updateOrder)
	:Component(_owner, _updateOrder)
	, owner_pendulum_(_ownerPendulum)
	, time_rate_state_(TimeRateState::Normal)
	, time_rate_(1.0f)
	, is_active_flg_(false)
{

	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
TimeZoneComponent::~TimeZoneComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void TimeZoneComponent::Init()
{
	time_rate_state_ = TimeRateState::Normal;
	time_rate_ = 1.0f;
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void TimeZoneComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void TimeZoneComponent::Update()
{
	// �^�C���]�[���̔{�������ق����g�������̂ł����ǂ�����΂����̂��l�������Ȃ��̂ŒN���ɑ����܂��B
	time_rate_ = 0.0f;

	is_active_flg_ = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	// �U��q�������Ă����
	if (is_active_flg_)
	{
	switch (time_rate_state_)
	{
	case TimeRateState::Slow:
		time_rate_ = 0.5f;
		break;

	case TimeRateState::Normal:
		time_rate_ = 1.0f;
		break;

	case TimeRateState::Fast:
		time_rate_ = 2.0f;
		break;
	}
	}

}


