//==================================================
// [LiftComponent.cpp] リフトコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトの挙動を制御するコンポーネント
//==================================================
/*----- インクルード -----*/


#include "../../GameObject.h"
#include "../../GameObject/Pendulum.h"



#include "LiftComponent.h"
#include "../TransformComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../PendulumMovementComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
LiftComponent::LiftComponent(GameObject* _owner, Pendulum* _pendulum, LiftComMoveState _moveState, int _updateOrder)
	:Component(_owner, _updateOrder)
	, lift_com_state_(LiftComState::Stop)
	, lift_com_move_state_(_moveState)
	, pendulum_(_pendulum)
	, max_move_distance_(0.0f)
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();

	start_pos_ = owner_transform_->GetPosition();
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
	max_move_distance_ = 0.0f;
	traveled_distance_ = { 0.0f, 0.0f };
	lift_com_state_ = LiftComState::Stop;
	this->InitDirection();
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
		break;
	}
	case LiftComponent::LiftComState::Move:
	{
		DirectX::SimpleMath::Vector3 liftPos = owner_transform_->GetPosition();
	
		auto moveSpeed = direction_ * owner_velocity_->GetSpeedRate();
		switch (lift_com_move_state_)
		{
		case LiftComponent::LiftComMoveState::length:	// 縦移動
		{
			// 移動距離を累積
			traveled_distance_.y += std::abs(moveSpeed.y);
			break;
		}
		case LiftComponent::LiftComMoveState::side:		// 横移動
		{
			// 移動距離を累積
			traveled_distance_.x += std::abs(moveSpeed.x);
			break;
		}
		case LiftComponent::LiftComMoveState::diagonalRight:	// 斜め移動（右）
		case LiftComponent::LiftComMoveState::diagonalLeft:	// 斜め移動（左）
		{
			// 移動距離を累積
			Vector2 normalizedDirection = {
				direction_.x / std::sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y),
				direction_.y / std::sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y)
			};
			traveled_distance_.x += std::abs(normalizedDirection.x);
			traveled_distance_.y += std::abs(normalizedDirection.y);
			break;
		}
		default:
			break;
		}
		// リフトの座標を支点として渡し続ける
		owner_velocity_->SetVelocity(Vector3(moveSpeed.x, moveSpeed.y, 0.0f));
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	}

}

//--------------------------------------------------
// @brief リフトの最大移動距離を設定
// @return 移動距離が最大距離を超えている: true, 超えていない: false
//--------------------------------------------------
bool LiftComponent::CheckTraveledDistance()
{
	bool switchFlg{};
	// 移動方向で処理を変えてます
	if (lift_com_move_state_ == LiftComMoveState::length || lift_com_move_state_ == LiftComMoveState::side)
		switchFlg = CheckLengthSideTraveled();	// 縦横移動の場合
	else
		switchFlg = CheckDiagonalTraveled();		// 斜め移動の場合

	// 移動距離が最大移動距離を超えたら
	if (switchFlg)
	{
		direction_ = -direction_;	// 移動方向を反転
		traveled_distance_ = { 0.0f, 0.0f };	// 移動距離をリセット
	}

	return switchFlg;
}

bool LiftComponent::CheckLengthSideTraveled()
{
	// 移動距離が最大移動距離を超えたら
	if (traveled_distance_.x >= max_move_distance_ && traveled_distance_.y >= max_move_distance_)
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
	if (traveled_distance_.x >= max_move_distance_ || traveled_distance_.y >= max_move_distance_)
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