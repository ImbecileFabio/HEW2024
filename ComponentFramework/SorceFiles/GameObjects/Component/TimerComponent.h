//==================================================
// [TimerComponent.h] �^�C�}�[�R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F�^�C�}�[�R���|�[�l���g
//if (!timer_component_->GetIsActive()) 	// �^�C�}�[���J�n
//{
//	timer_component_->StartTimer();
//}
//if (timer_component_->GetIsTriggered())	// �^�C�}�[���o�߂��āA�g���K�[�����������ꍇ
//{
//	timer_component_->StopTimer();			// �g���K�[������������^�C�}�[���~�߂�
//}
//==================================================
#ifndef TIMER_COMPONENT_H_
#define TIMER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// Hoge�R���|�[�l���g
//--------------------------------------------------
class TimerComponent : public Component
{
public:
    TimerComponent(GameObject* _owner, float _triggerTime, int _updateOrder = 50);
    ~TimerComponent();

    void Init()   override;
    void Uninit() override;
    void Update() override;

	void StartTimer();        // �^�C�}�[���J�n
	void StopTimer();         // �^�C�}�[���~
	void ResetTimer();        // �^�C�}�[�����Z�b�g

	void SetTriggerTime(float _triggerTime); // �g���K�[���Ԃ̐ݒ�

    bool GetIsActive()    const; // �^�C�}�[���ғ����Ă��邩�ǂ���
	bool GetIsTriggered() const; // �g���K�[�������������ǂ���

    TypeID GetComponentType(void) const override { return TypeID::TimerComponent; }
private:
    float elapse_time_;   // �o�ߎ���
	float trigger_time_;  // �g���K�[����
	bool is_active_;      // �^�C�}�[�����쒆���ǂ���
	bool is_triggered_;   // �g���K�[�������������ǂ���
};
#endif // TIMER_COMPONENT_H_
