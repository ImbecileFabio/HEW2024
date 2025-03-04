//==================================================
// [TimeZoneComponent.h] タイムゾーンコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイムゾーンの処理を行うコンポーネント
//==================================================
#ifndef TIME_ZONE_COMPONENT_H_
#define TIME_ZONE_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEコンポーネント
//--------------------------------------------------
class TimeZoneComponent : public Component
{
public:
	// 倍率の種類
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
//必要な機能
// .オブジェクトの速度を変更する処理
// 現在の倍率を保持しておいてそれを外に取り出せればよさそう
// それぞれのonCollisionEnterで速度を変更する処理を書けばかな
// そうするとやはりコリジョンから出た時の処理も必要になるか...
// 
// .オブジェクトを止める処理
// 上と同じで倍率を0にすればよさそう
// 
// .振り子の長さに合わせて速度を変更する処理
// 振り子から長さの段階を取得してそれに応じてStateを分ければよさそう？
// 
// .振り子の長さにサイズを合わせる処理
// 上の処理に似た感じで行けるかも
// 
//
//
