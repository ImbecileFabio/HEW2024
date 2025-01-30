//==================================================
// [TimerComponent.cpp] タイマーコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：タイマーコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "TimerComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
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
// @brief デストラクタ
//--------------------------------------------------
TimerComponent::~TimerComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void TimerComponent::Init()
{
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void TimerComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void TimerComponent::Update()
{
	// タイマーが稼働していない場合は処理をスキップ
	if (!is_active_) return;
	// 経過時間を加算
	elapse_time_ += delta_time_;
	// 経過時間がトリガー時間を超えた場合
	if (elapse_time_ >= trigger_time_)
	{
		is_triggered_ = true;
	}
}
//--------------------------------------------------
// @brief タイマーの開始
//--------------------------------------------------
void TimerComponent::StartTimer()
{
	is_active_	  = true;
	elapse_time_  = 0.0f;
	is_triggered_ = false;
}
//--------------------------------------------------
// @brief タイマーの停止
//--------------------------------------------------
void TimerComponent::StopTimer()
{
	is_active_ = false;
}
//--------------------------------------------------
// @brief タイマーのリセット
//--------------------------------------------------
void TimerComponent::ResetTimer()
{
	elapse_time_  = 0.0f;
	is_active_	  = false;
	is_triggered_ = false;
}
//--------------------------------------------------
// @brief トリガー時間の設定
// @param _triggerTime トリガー時間
//--------------------------------------------------
void TimerComponent::SetTriggerTime(float _triggerTime)
{
	trigger_time_ = _triggerTime;
}
//--------------------------------------------------
// @brief タイマーが稼働しているかどうか
// @return タイマーが稼働: true, していない: false
//--------------------------------------------------
bool TimerComponent::GetIsActive() const
{
	return is_active_;
}
//--------------------------------------------------
// @brief トリガーが発生したかどうか
// @return トリガーが発生: true, していない: false
//--------------------------------------------------
bool TimerComponent::GetIsTriggered() const
{
	return is_triggered_;
}