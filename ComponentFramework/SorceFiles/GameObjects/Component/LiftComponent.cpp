#include "LiftComponent.h"
#include "../GameObject/Pendulum.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
LiftComponent::LiftComponent(Pendulum* _pendulum, MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameObject* _owner, int _updateOrder)
	:Component	(_owner, _updateOrder)
	, maxPos_	(_maxPos)	// 正方向の最大座標
	, minPos_	(_minPos)	// 負方向の最大座標
	, pendulum_	(_pendulum)	// リフトの動きと連動させる振り子の参照
	, switchFg_	(false)		// スイッチフラグ
	, moveState_(_moveState)// 移動状態
{
	this->Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
LiftComponent::~LiftComponent(void)
{
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void LiftComponent::Init()
{
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void LiftComponent::Update()
{
	bool moveFg = pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
	auto velocity = owner_ ->GetComponent<VelocityComponent>();
	if (!velocity)
	{
		std::cout << std::format("[LiftComponent]-> コンポーネントが取得できませんでした\n");
		return;
	}
	if (moveFg)
	{
		DirectX::SimpleMath::Vector3 liftPos = owner_->GetTransformComponent()->GetPosition();

		switch (moveState_)
		{
		case LiftComponent::MoveState::length:	// 縦移動
			if (!switchFg_)
			{
				velocity->SetVelocity({ 0.0f, 2.0f, 0.0f });
				if (liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else
			{
				velocity->SetVelocity({ 0.0f, -2.0f, 0.0f });
				if (liftPos.y <= minPos_.y)
				{
					switchFg_ = false;
				}
			}
			break;
		case LiftComponent::MoveState::side:		// 横移動
			if (!switchFg_)
			{
				velocity->SetVelocity({ 2.0f, 0.0f, 0.0f });
				if (liftPos.x >= maxPos_.x)
				{
					switchFg_ = true;
				}
			}
			else
			{
				velocity->SetVelocity({ -2.0f, 0.0f, 0.0f });
				if (liftPos.x <= minPos_.x)
				{
					switchFg_ = false;
				}
			}
			break;
		case LiftComponent::MoveState::diagonal:	// 斜め移動
			if (!switchFg_)
			{
				velocity->SetVelocity({ 2.0f, 2.0f, 0.0f });
				if (liftPos.x >= maxPos_.x && liftPos.y >= maxPos_.y)
				{
					switchFg_ = true;
				}
			}
			else {
				velocity->SetVelocity({ -2.0f, -2.0f, 0.0f });
				if (liftPos.x <= minPos_.x && liftPos.y <= minPos_.y)
				{
					switchFg_ = false;
				}
			}
			break;
		default:
			break;
		}
		// リフトの座標を支点として渡し続ける
		pendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(liftPos);
	}
	else
	{
		velocity->SetVelocity({ 0.0f, 0.0f, 0.0f });
	}
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void LiftComponent::Uninit()
{
}
