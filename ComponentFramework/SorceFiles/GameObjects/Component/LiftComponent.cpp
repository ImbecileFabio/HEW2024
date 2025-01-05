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
	this->Uninit();
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
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void LiftComponent::Uninit()
{
}
