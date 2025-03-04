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
	// リフトが存在しない場合
	if (!current_lift_) return;

	// 動いている場合
	if (current_lift_->GetLiftState() == Lift::LiftState::Move)
	{

		auto ownerTransform = owner_->GetTransformComponent();
		auto ownerPos = ownerTransform->GetPosition();
		auto liftHitBox = current_lift_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
		auto liftVelocity = current_lift_->GetComponent<VelocityComponent>();

		// Y軸の位置調整
		float targetY = liftHitBox.max_.y + (ownerTransform->GetSize().y * 0.5f);

		const float smoothFactor = 0.15f;
		float newY = std::lerp(ownerPos.y, targetY, smoothFactor);

		// 位置変更
		ownerTransform->SetPosition(ownerPos.x, newY, ownerPos.z);


		// 速度の同期
		auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
		if (ownerVelocity && liftVelocity)
		{
			Vector3 liftVel = liftVelocity->GetVelocity();
			ownerVelocity->SetVelocity(liftVel);
			ownerVelocity->SetSpeedRate(liftVelocity->GetSpeedRate());
		}
	}
	// 停止状態の場合
	else if (current_lift_->GetLiftState() == Lift::LiftState::Stop)
	{
		current_lift_ = nullptr;
	}
}

//--------------------------------------------------
// @param _lift: リフト
// @brief リフトをセット
//--------------------------------------------------
void LiftInteractionComponent::SetLift(Lift* _lift)
{
	if (!_lift || _lift->GetLiftState() == Lift::LiftState::Stop)
	{
		current_lift_ = nullptr;
		return;
	}

	// 既にセットされているリフトと同じなら虫場合は無視
	if (current_lift_ == _lift) return;


	// 前のリフトとの関連を解除
	if (current_lift_) {
		auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
		ownerVelocity->SetVelocity(Vector3::Zero);
	}

	// 新しいリフトをセット
	current_lift_ = _lift;

	// 初期速度をセット
	auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
	auto liftVelocity = _lift->GetComponent<VelocityComponent>();
	if (ownerVelocity && liftVelocity)
	{
		ownerVelocity->SetVelocity(liftVelocity->GetVelocity());
		ownerVelocity->SetSpeedRate(liftVelocity->GetSpeedRate());
	}
}


//--------------------------------------------------
// @param _lift: リフト
// @brief リフトの中央に触れているか
// @return 触れている: true, 触れていない: false
//--------------------------------------------------
bool LiftInteractionComponent::IsTouchingLiftCenter(Lift* _lift)
{
	if (!_lift) return false;

	// リフトの中心と幅を取得
	auto liftHitbox = _lift->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
	float liftCenter = (liftHitbox.max_.x + liftHitbox.min_.x) * 0.5f;
	float liftWidth = liftHitbox.max_.x - liftHitbox.min_.x;

	// プレイヤーのヒットボックスを取得
	auto ownerPos = owner_->GetTransformComponent()->GetPosition();

	// プレイヤーがリフトの中心付近にいるかチェック
	float allowedOffset = liftWidth * 0.4f;  // リフト幅の40%を許容範囲とする
	return abs(ownerPos.x - liftCenter) < allowedOffset;
}
