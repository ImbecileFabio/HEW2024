//==================================================
// [SteePillarFloorDown.cpp] 鉄柱ギミックコンポーネントソース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：鉄柱ギミックコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "SteePillarFloorMove.h"
#include "../../../GameObject.h"
#include "../../RigidbodyComponent/VelocityComponent.h"
#include "../../GravityComponent.h"
#include "../../ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarFloorMove::SteePillarFloorMove(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SteePillarFloorMove::~SteePillarFloorMove()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarFloorMove::Init()
{
	owner_transform_	= owner_->GetTransformComponent();
	owner_velocity_		= owner_->GetComponent<VelocityComponent>();
	owner_box_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_gravity_		= owner_->GetComponent<GravityComponent>();

	direction_ = { 0.0f, -1.0f };	// 初期の向きは下方向
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void SteePillarFloorMove::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarFloorMove::Update()
{
	switch (floorState_)
	{
	case SteePillarFloorMove::FloorState::Up:
		direction_ = { direction_.x, direction_.y };	// 上方向に切り替え
		owner_velocity_->SetVelocity({ 0.0f ,direction_.y * 1.0f, 0.0f });	// 上方向に移動
		break;
	case SteePillarFloorMove::FloorState::Stop:
		owner_velocity_->ResetVelocity();				// 停止状態になったら加速をなしにする
		break;
	case SteePillarFloorMove::FloorState::Falling:		// 落下状態
		owner_gravity_->SetUseGravityFlg(true);
		break;
	case SteePillarFloorMove::FloorState::OnLift:		// リフトと接触状態
		// リフトと追従
		break;
	case SteePillarFloorMove::FloorState::OnTile:		// タイルと接触状態
		// タイルと追従
		break;
	case SteePillarFloorMove::FloorState::OnLiftAndTile:// リフトとタイルの同時接触状態
		// リフトとタイルと追従
		break;
	case SteePillarFloorMove::FloorState::Down:			// 下方向に切り替え
		if (owner_gravity_->CheckGroundCollision())	// 地面に接触していたら
		{
			owner_gravity_->SetUseGravityFlg(false);// 重力を無効にする
			// 今接触しているオブジェクトによってStateを変化させる

		}
		else
		{
			owner_gravity_->SetUseGravityFlg(true);	// 重力を有効にする
		}
		//direction_ = { direction_.x, -direction_.y };	// 下方向に切り替え
		//owner_velocity_->SetVelocity({ 0.0f , direction_.y * 1.0f, 0.0f });	// 下方向に移動
		break;
	default:
		break;
	}
}
