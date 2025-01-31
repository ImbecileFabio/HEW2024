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
#include "../../Component/ColliderComponent/BoxColliderComponent.h"

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
	if (!current_lift_) return;

	// 動いている場合
	if (current_lift_->GetLiftState() == Lift::LiftState::Move)
	{
		auto ownerTransform = owner_->GetTransformComponent();
		auto ownerSize = ownerTransform->GetSize();
		auto ownerPos = ownerTransform->GetPosition();
		auto liftHitBox = current_lift_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();

		// y軸の位置を補正する
		auto newY = (liftHitBox.max_.y + ownerSize.y / 2) - 2.5f;
		ownerTransform->SetPosition(ownerPos.x, newY, ownerPos.z);

		// リフトの速度と速度倍率を取得し、所有者に設定
		auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();
		owner_->GetComponent<VelocityComponent>()->SetVelocity(liftVelocity->GetVelocity());
		owner_->GetComponent<VelocityComponent>()->SetSpeedRate(liftVelocity->GetSpeedRate());
	}
	// 停止している場合
	else if (current_lift_->GetLiftState() == Lift::LiftState::Stop) {
		// リフトの参照を切る
		current_lift_ = nullptr;
	}

}

//--------------------------------------------------
// @param _lift: リフト
// @brief リフトをセット
//--------------------------------------------------
void LiftInteractionComponent::SetLift(Lift* _lift)
{
    if (current_lift_ == _lift) return;  // すでに同じリフトなら何もしない

    if (_lift->GetLiftState() == Lift::LiftState::Stop) return; // 停止リフトには乗らない

    // まだ乗っていないが、少し浮いている場合も `SetLift()` する
	if (!current_lift_ || IsTouchingLiftCenter(_lift))
	{
		current_lift_ = _lift;
		owner_->GetComponent<VelocityComponent>()->SetVelocity(Vector3::Zero); // 速度リセット
	}
}


//--------------------------------------------------
// @param _lift: リフト
// @brief リフトの中央に触れているか
// @return 触れている: true, 触れていない: false
//--------------------------------------------------
bool LiftInteractionComponent::IsTouchingLiftCenter(Lift* _lift)
{
	// Liftの中心
	auto liftCenter = _lift->GetTransformComponent()->GetPosition().x;

	// ownerのAABB
	auto ownerHitbox = owner_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();

	return (liftCenter > ownerHitbox.min_.x && liftCenter < ownerHitbox.max_.x);
}
