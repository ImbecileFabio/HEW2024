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

#include "../../Component/RenderComponent/DebugColliderDrawComponent.h"
#include "../../GameObject/Robot.h"
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
	sprite_component_		= new SpriteComponent(this, "steelpillar_floor_center", 70);
	gravity_component_		= new GravityComponent(this);
	box_collider_component_ = new BoxColliderComponent(this);
	velocity_component_		= new VelocityComponent(this);
	event_component_		= new ColliderEventComponent(this);

	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);


	auto size = transform_component_->GetSize();
	box_collider_component_->SetSize(size.x * 0.99f, size.y * 0.6);
	box_collider_component_->SetOffset(Vector3(0.0f, -size.y * 0.25f, 0.0f));

	new DebugColliderDrawComponent(this);

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
bool isRobotOn = false;
void SteePillarFloor::OnCollisionEnter(GameObject* _other)
{
	if (state_ == State::Paused) return;
	if (_other->GetType() == TypeID::Lift)
	{
		leftTilePosition_ = _other->GetTransformComponent()->GetPosition();
		stee_pillar_floor_group_->AlignSteePillarFloorTilesWithTile(leftTilePosition_.y);
		stee_pillar_floor_group_->SetHitLeft(true);

	}
	if (_other->GetType() == TypeID::Tile)	// タイルと鉄柱床タイルが接触したら
	{
		if (!stee_pillar_floor_group_->GetIsHitLift_())
		{
			tilePosition_ = _other->GetTransformComponent()->GetPosition();
			stee_pillar_floor_group_->AlignSteePillarFloorTilesWithTile(tilePosition_.y);
			stee_pillar_floor_group_->SetHitTile(true);
		}
	}
	if (_other->GetType() == TypeID::Robot)
	{
		auto robotPos = _other->GetTransformComponent()->GetPosition();
		_other->GetTransformComponent()->SetPositionY(robotPos.y);
		stee_pillar_floor_group_->SetIsRobotOn(true);
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

