//==================================================
// [TimeZoneComponent.h] �^�C���]�[���R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C���]�[���̏������s���R���|�[�l���g
//==================================================
#ifndef TIME_ZONE_COMPONENT_H_
#define TIME_ZONE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�R���|�[�l���g
//--------------------------------------------------
class TimeZoneComponent : public Component
{
public:
	// �{���̎��
    enum class TimeRateState {
        Slow,
        Normal,
		Fast
    };

    TimeZoneComponent(GameObject* _owner, GameObject* _ownerPendulum, int _updateOrder = 11);
    ~TimeZoneComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

	void SetTimeRateState(TimeRateState _rate) { time_rate_state_ = _rate; }

    void SetTimeRate(float _rate) { time_rate_ = _rate; }
	auto GetTimeRate(void) { return time_rate_; }

	void SetActiveFlg(bool _flg) { is_active_flg_ = _flg; }
	auto GetActiveFlg(void) { return is_active_flg_; }

    TypeID GetComponentType(void) const override { return TypeID::TimeZoneComponent; }
private:

	GameObject* owner_pendulum_;

    TimeRateState time_rate_state_;
    float time_rate_;
    bool is_active_flg_;
    


};
#endif // TIME_ZONE_COMPONENT_H_


//==================================================
//�K�v�ȋ@�\
// .�I�u�W�F�N�g�̑��x��ύX���鏈��
// ���݂̔{����ێ����Ă����Ă�����O�Ɏ��o����΂悳����
// ���ꂼ���onCollisionEnter�ő��x��ύX���鏈���������΂���
// ��������Ƃ�͂�R���W��������o�����̏������K�v�ɂȂ邩...
// 
// .�I�u�W�F�N�g���~�߂鏈��
// ��Ɠ����Ŕ{����0�ɂ���΂悳����
// 
// .�U��q�̒����ɍ��킹�đ��x��ύX���鏈��
// �U��q���璷���̒i�K���擾���Ă���ɉ�����State�𕪂���΂悳�����H
// 
// .�U��q�̒����ɃT�C�Y�����킹�鏈��
// ��̏����Ɏ��������ōs���邩��
// 
//
//
