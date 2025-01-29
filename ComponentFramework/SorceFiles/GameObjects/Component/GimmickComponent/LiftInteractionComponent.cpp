//==================================================
// [LiftInteractionComponent.cpp]リフトインタラクションコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：リフトに触れるとコンポーネントの所有者に動きを伝える処理
//==================================================
/*----- インクルード -----*/
#include <SimpleMath.h>

#include "LiftInteractionComponent.h"

#include "../../GameObject/Lift.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
LiftInteractionComponent::LiftInteractionComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
LiftInteractionComponent::~LiftInteractionComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void LiftInteractionComponent::Init()
{
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void LiftInteractionComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void LiftInteractionComponent::Update()
{
	// リフトが存在する場合
	if (current_lift_) {
		// 動いている場合
		if(current_lift_->GetLiftState() == Lift::LiftState::Move)
		{
			// リフトの速度と速度倍率を取得し、所有者に設定
			auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();
			owner_->GetComponent<VelocityComponent>()->SetVelocity(liftVelocity->GetVelocity());
			owner_->GetComponent<VelocityComponent>()->SetSpeedRate(liftVelocity->GetSpeedRate());
		}
		// 停止している場合
		else if(current_lift_->GetLiftState() == Lift::LiftState::Stop) {
			// リフトの参照を切る
			current_lift_ = nullptr;
		}

	}
}

void LiftInteractionComponent::SetLift(Lift* _lift)
{
	if (current_lift_ == _lift) return;

	current_lift_ = _lift;

}
