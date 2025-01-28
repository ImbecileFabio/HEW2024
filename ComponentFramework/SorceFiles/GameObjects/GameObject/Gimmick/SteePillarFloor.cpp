//=================================================================
// [SteePillarFloor.cpp] 鉄柱オブジェクトのCPP
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱オブジェクトの実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarFloor.h"
#include "../../../TileMapManager.h"
#include "../Gimmick/Group/SteePillarFloorGroup.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GravityComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarFloor::SteePillarFloor(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillar")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarFloor::~SteePillarFloor(void)
{
	delete sprite_component_;
	delete gravity_component_;
	delete box_collider_component_;
	delete velocity_component_;
	delete event_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarFloor::InitGameObject(void)
{
	sprite_component_		= new SpriteComponent(this, "steelpillar_floor_center");
	gravity_component_		= new GravityComponent(this);
	box_collider_component_ = new BoxColliderComponent(this);
	velocity_component_		= new VelocityComponent(this);
	event_component_		= new ColliderEventComponent(this);
	//transform_component_->SetSize(TILE_SIZE_X * 1.5f, TILE_SIZE_Y * 1.5f);
	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);
	box_collider_component_->SetSize(transform_component_->GetSize().x, transform_component_->GetSize().y * 0.2f);

	auto f = std::function<void(GameObject*)>(std::bind(&SteePillarFloor::OnCollisionEnter, this, std::placeholders::_1));
	event_component_->AddEvent(f);
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarFloor::UpdateGameObject(void)
{
	if (isDown_)
	{
		gravity_component_->SetUseGravityFlg(true);
	}
	else
	{
		gravity_component_->SetUseGravityFlg(false);
		velocity_component_->ResetVelocity();
	}
	stee_pillar_floor_group_->UpdateSteePillarFloorTilePositions();
}
//--------------------------------------------------
// @brief 当たり判定実行処理
//--------------------------------------------------
void SteePillarFloor::OnCollisionEnter(GameObject* _other)
{
	if (state_ == State::Paused) return;
	if (_other->GetType() == TypeID::Tile)	// タイルと鉄柱床タイルが接触したら
	{
		float posY = transform_component_->GetPosition().y;
		transform_component_->SetPositionY(posY + offsetY_);
		stee_pillar_floor_group_->SetHitTile(true);
	}
}
//--------------------------------------------------
// @brief グループの参照を設定
// @param _stee_pillar_floor_group[鉄柱の足場グループ]
//--------------------------------------------------
void SteePillarFloor::SetSteePillarFloorGroup(SteePillarFloorGroup* _stee_pillar_floor_group)
{
	stee_pillar_floor_group_ = _stee_pillar_floor_group;
}

