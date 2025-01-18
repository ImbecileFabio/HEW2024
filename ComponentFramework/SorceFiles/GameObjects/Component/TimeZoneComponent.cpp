//==================================================
// [TimeZoneComponent.cpp] HOGEコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：HOGEコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "TimeZoneComponent.h"

#include "../GameObject.h"

#include "PendulumMovementComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
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
// @brief デストラクタ
//--------------------------------------------------
TimeZoneComponent::~TimeZoneComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void TimeZoneComponent::Init()
{
	time_rate_state_ = TimeRateState::Normal;
	time_rate_ = 1.0f;
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void TimeZoneComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void TimeZoneComponent::Update()
{
	// タイムゾーンの倍率高いほうを使いたいのですがどうすればいいのか考えたくないので誰かに託します。
	time_rate_ = 0.0f;

	is_active_flg_ = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	// 振り子が動いていれば
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


