//==================================================
// [TimerComponent.h] タイマーコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：タイマーコンポーネント
//if (!timer_component_->GetIsActive()) 	// タイマーを開始
//{
//	timer_component_->StartTimer();
//}
//if (timer_component_->GetIsTriggered())	// タイマーが経過して、トリガーが発生した場合
//{
//	timer_component_->StopTimer();			// トリガーが発生したらタイマーを止める
//}
//==================================================
#ifndef TIMER_COMPONENT_H_
#define TIMER_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Hogeコンポーネント
//--------------------------------------------------
class TimerComponent : public Component
{
public:
    TimerComponent(GameObject* _owner, float _triggerTime, int _updateOrder = 50);
    ~TimerComponent();

    void Init()   override;
    void Uninit() override;
    void Update() override;

	void StartTimer();        // タイマーを開始
	void StopTimer();         // タイマーを停止
	void ResetTimer();        // タイマーをリセット

	void SetTriggerTime(float _triggerTime); // トリガー時間の設定

    bool GetIsActive()    const; // タイマーが稼働しているかどうか
	bool GetIsTriggered() const; // トリガーが発生したかどうか

    TypeID GetComponentType(void) const override { return TypeID::TimerComponent; }
private:
    float elapse_time_;   // 経過時間
	float trigger_time_;  // トリガー時間
	bool is_active_;      // タイマーが動作中かどうか
	bool is_triggered_;   // トリガーが発生したかどうか
};
#endif // TIMER_COMPONENT_H_
