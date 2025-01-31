//==================================================
// [LiftComponent.cpp] リフトコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトの挙動を制御するコンポーネント
//==================================================
/*----- インクルード -----*/


#include "../../GameObject.h"
#include "../..//GameObject/Pendulum.h"

#include "../../../AudioManager.h"
#include "../../GameObject/Lift.h"

#include "LiftComponent.h"
#include "../TransformComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../PendulumMovementComponent.h"
#include "../../GameObject/Gimmick/Group/LiftGroup.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
LiftComponent::LiftComponent(GameObject* _owner, LiftComMoveState _moveState, Vector3 _startPos, Vector3 _endPos, Pendulum* _pendulum, int _updateOrder)
	:Component(_owner, _updateOrder)
	, lift_com_state_(LiftComState::Stop)
	, lift_com_move_state_(_moveState)
	, pendulum_(_pendulum)
	, start_pos_(_startPos)
	, end_pos_(_endPos)
	, turn_flg_(false)
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();

	float dx = end_pos_.x - start_pos_.x;
	float dy = end_pos_.y - start_pos_.y;
	max_move_distance_ = std::sqrt(dx * dx + dy * dy);

	// 移動方向
	if (max_move_distance_ != 0.0f)
		direction_ = { dx / max_move_distance_, dy / max_move_distance_ };
	else
		direction_ = { 0.0f, 0.0f };

	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
LiftComponent::~LiftComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void LiftComponent::Init()
{
	traveled_distance_ = { 0.0f, 0.0f };
	lift_com_state_ = LiftComState::Stop;																															
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void LiftComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void LiftComponent::Update()
{
	if (!pendulum_) return;

	switch (lift_com_state_)
	{
	case LiftComState::Stop:
	{
		owner_velocity_->SetVelocity({ 0.0f, 0.0f, 0.0f });
		AudioManager::GetInstance()->Stop(this->GetOwner()->GetType(),this->GetOwner()->GetObjectFier());
		break;
	}
	case LiftComState::Wait:
	{
		owner_velocity_->SetVelocity({ 0.0f, 0.0f, 0.0f });
		break;
	}

	case LiftComponent::LiftComState::Move:
	{
		switch (lift_com_move_state_)
		{
		case LiftComponent::LiftComMoveState::length:	// 縦移動
		{
			// 移動量をセット
			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
			// 移動距離を累積
			traveled_distance_.y += std::abs(direction_.y) * owner_velocity_->GetSpeedRate();
			break;
		}
		case LiftComponent::LiftComMoveState::side:		// 横移動
		{
			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));
			// 移動距離を累積
			traveled_distance_.x += std::abs(direction_.x) * owner_velocity_->GetSpeedRate();
			break;
		}
		case LiftComponent::LiftComMoveState::diagonalRight:	// 斜め移動（右）
		case LiftComponent::LiftComMoveState::diagonalLeft:	// 斜め移動（左）
		{

			owner_velocity_->SetVelocity(Vector3(direction_.x, direction_.y, 0.0f));

			// 合成距離を累積
			auto stepDistance = std::sqrt(
				(direction_.x * owner_velocity_->GetSpeedRate()) * (direction_.x * owner_velocity_->GetSpeedRate()) +
				(direction_.y * owner_velocity_->GetSpeedRate()) * (direction_.y * owner_velocity_->GetSpeedRate())
			);

			traveled_distance_.x += stepDistance;
			traveled_distance_.y += stepDistance;
			break;
		}
		default:
			break;
		}

		if (!AudioManager::GetInstance()->GetPlayingState(this->GetOwner()->GetType(), this->GetOwner()->GetObjectFier()))
			AudioManager::GetInstance()->Play(this->GetOwner()->GetType(), this->GetOwner()->GetObjectFier());
	}
	}

		// リフトの座標を支点として渡し続ける
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(owner_transform_->GetPosition());
}

//--------------------------------------------------
// @brief リフトの最大移動距離を設定
// @return 移動距離が最大距離を超えている: true, 超えていない: false
//--------------------------------------------------
bool LiftComponent::CheckTraveledDistance()
{
	bool switchFlg = false;
	// 移動方向で処理を変えてます
	if (lift_com_move_state_ == LiftComMoveState::length || lift_com_move_state_ == LiftComMoveState::side)
		switchFlg = CheckLengthSideTraveled();	// 縦横移動の場合
	else
		switchFlg = CheckDiagonalTraveled();		// 斜め移動の場合

	// 移動距離が最大移動距離を超えたら
	if (switchFlg)
	{
		// 座標のずれをなくす
		if (turn_flg_)
		{
			owner_transform_->SetPosition(start_pos_);
		}
		else
		{
			owner_transform_->SetPosition(end_pos_);
		}

		turn_flg_ = !turn_flg_;	// 次の補正位置を切り替える
		direction_ = -direction_;	// 移動方向を反転
		traveled_distance_ = { 0.0f, 0.0f };	// 移動距離をリセット
	}

	return switchFlg;
}

bool LiftComponent::CheckLengthSideTraveled()
{
	// 移動距離が最大移動距離を超えたら
	if (traveled_distance_.x >= max_move_distance_ || traveled_distance_.y >= max_move_distance_)
	{
		return true;
	}

	return false;
}

//--------------------------------------------------
// @brief リフトの移動距離が最大距離を超えているか
// @return : はい: true, いいえ: false
//--------------------------------------------------
bool LiftComponent::CheckDiagonalTraveled()
{
	// 移動距離が最大移動距離を超えたら
	if (traveled_distance_.x >= max_move_distance_ && traveled_distance_.y >= max_move_distance_)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------
// @brief 移動方向の初期化
//--------------------------------------------------
void LiftComponent::InitDirection() {

	switch (lift_com_move_state_) {
	case LiftComponent::LiftComMoveState::length: // 縦移動
		direction_ = { 0.0f, 1.0f }; // 上方向
		break;
	case LiftComponent::LiftComMoveState::side: // 横移動
		direction_ = { 1.0f, 0.0f }; // 右方向
		break;
	case LiftComponent::LiftComMoveState::diagonalRight: // 斜め右移動
		direction_ = { 1.0f, 1.0f }; // 右上方向
		break;
	case LiftComponent::LiftComMoveState::diagonalLeft: // 斜め左移動
		direction_ = { -1.0f, 1.0f }; // 左上方向
		break;
	default:
		direction_ = { 0.0f, 0.0f }; // 静止
		break;
	}
}