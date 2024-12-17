//==================================================
// [RobotMoveComponent.cpp] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include "RobotMoveComponent.h"

#include "../GameObject.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(20.0f)
{

	this->Init();
}


//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RobotMoveComponent::~RobotMoveComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void RobotMoveComponent::Init()
{
	right_move_flg_ = true;	// 右移動
	on_ground_flg_ = false;	// 空中
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void RobotMoveComponent::Uninit()
{

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void RobotMoveComponent::Update()
{
	auto velocity = this->owner_->GetComponent<VelocityComponent>();
	auto collider = this->owner_->GetComponent<BoxColliderComponent>();
	auto transform = this->owner_->GetComponent<TransformComponent>();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> コンポーネントが取得できませんでした\n");
		return; 
	}

	CheckTurnAround(*transform, *collider);

	if (right_move_flg_)
	{
		velocity->SetVelocity(Vector3(speed_, 0, 0));
	}
	else
	{
		velocity->SetVelocity(Vector3(-speed_, 0, 0));
	}

}


//--------------------------------------------------
// 地面の検出処理
//--------------------------------------------------
void RobotMoveComponent::CheckTurnAround(TransformComponent& _transform, BoxColliderComponent& _collider)
{
	// 地面の検出を実装する予定
	
	auto pos = _transform.GetPosition();
	auto size = _collider.GetBoxSize();
	// 画面外に出そうになるなら
	if (pos.x < (-960 - size.x / 2))
	{
		right_move_flg_ = true;
	}
	else if (pos.x > (960 + size.x / 2))
	{
		right_move_flg_ = false;
	}
}