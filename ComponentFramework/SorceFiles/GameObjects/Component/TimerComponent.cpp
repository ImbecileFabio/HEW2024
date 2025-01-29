//==================================================
// [TimerComponent.cpp] �^�C�}�[�R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F�^�C�}�[�R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
#include "TimerComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
TimerComponent::TimerComponent(GameObject* _owner, float _triggerTime ,int _updateOrder)
	:Component(_owner, _updateOrder)
	, elapse_time_(0.0f)
	, old_time_(0.0f)
	, trigger_time_(_triggerTime)
	, is_active_(false)
	, is_triggered_(false)
{
	this->Init();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
TimerComponent::~TimerComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void TimerComponent::Init()
{
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void TimerComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void TimerComponent::Update()
{
	// �^�C�}�[���ғ����Ă��Ȃ��ꍇ�͏������X�L�b�v
	if (!is_active_) return;
	// �o�ߎ��Ԃ����Z
	elapse_time_ += delta_time_;
	// �o�ߎ��Ԃ��g���K�[���Ԃ𒴂����ꍇ
	if (elapse_time_ >= trigger_time_)
	{
		is_triggered_ = true;
	}
}
//--------------------------------------------------
// @brief �^�C�}�[�̊J�n
//--------------------------------------------------
void TimerComponent::StartTimer()
{
	is_active_	  = true;
	elapse_time_  = 0.0f;
	is_triggered_ = false;
}
//--------------------------------------------------
// @brief �^�C�}�[�̒�~
//--------------------------------------------------
void TimerComponent::StopTimer()
{
	is_active_ = false;
}
//--------------------------------------------------
// @brief �^�C�}�[�̃��Z�b�g
//--------------------------------------------------
void TimerComponent::ResetTimer()
{
	elapse_time_  = 0.0f;
	is_active_	  = false;
	is_triggered_ = false;
}
//--------------------------------------------------
// @brief �g���K�[���Ԃ̐ݒ�
// @param _triggerTime �g���K�[����
//--------------------------------------------------
void TimerComponent::SetTriggerTime(float _triggerTime)
{
	trigger_time_ = _triggerTime;
}
//--------------------------------------------------
// @brief �^�C�}�[���ғ����Ă��邩�ǂ���
// @return �^�C�}�[���ғ�: true, ���Ă��Ȃ�: false
//--------------------------------------------------
bool TimerComponent::GetIsActive() const
{
	return is_active_;
}
//--------------------------------------------------
// @brief �g���K�[�������������ǂ���
// @return �g���K�[������: true, ���Ă��Ȃ�: false
//--------------------------------------------------
bool TimerComponent::GetIsTriggered() const
{
	return is_triggered_;
}