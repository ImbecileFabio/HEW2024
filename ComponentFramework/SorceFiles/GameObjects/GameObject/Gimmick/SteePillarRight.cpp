//=================================================================
// [SteePillarRight.cpp] 鉄柱オブジェクトのCPP
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱オブジェクトの実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarRight.h"
#include "Group/SteePillarRightGroup.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../Component/GravityComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarRight::SteePillarRight(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRight")
	, sprite_component_(nullptr)
	, animation_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarRight::~SteePillarRight(void)
{
	delete sprite_component_;
	delete animation_component_;
	delete gravity_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarRight::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal", 1);
	animation_component_ = new AnimationComponent(this, sprite_component_);
	velocity_component_ = new VelocityComponent(this);
	gravity_component_ = new GravityComponent(this);
	gravity_component_->SetGravity(-1.2f);
	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarRight::UpdateGameObject(void)
{
	if (isDown_)
	{
		gravity_component_->SetUseGravityFlg(true);
	}
	else
	{
		//auto pos = transform_component_->GetPosition();
		//transform_component_->SetPosition()
	}

	// 床のVelocityが動いていたら
	if (isFloorVelocityStop_)
	{
		// 床の位置を取得
		auto floorPos = floorPosition_;
		Vector3 pos = transform_component_->GetPosition();

		// 床との差分をオフセットとして設定
		offset_ = Vector3(floorPos.x - pos.x, floorPos.y - pos.y, 0.0f);

		// 位置をオフセットを適用して更新
		transform_component_->SetPositionY(pos.y + offset_.y);
	}
	else
	{

	}

}
//--------------------------------------------------
// @brief 所有されるグループの参照を設定
// @param _group[鉄柱グループ]
//--------------------------------------------------
void SteePillarRight::SetPillarRightGroup(SteePillarRightGroup* _group)
{
	stee_pillar_right_group_ = _group;
}

