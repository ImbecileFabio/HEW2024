//=================================================================
// [SteePillarLeftTop.cpp] 鉄柱オブジェクトの一番上
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱オブジェクトの一番上実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarLeftTop.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarLeftTop::SteePillarLeftTop(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeftTop")
	, sprite_component_(nullptr)
	, animation_component_(nullptr)
	, offsetFg_(false)
	, offset_(0.0f, 0.0f)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarLeftTop::~SteePillarLeftTop(void)
{
	delete sprite_component_;
	delete animation_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarLeftTop::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
	//animation_component_ = new AnimationComponent(this, sprite_component_);
	offset_ = { 11.0f, 0.0f };
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarLeftTop::UpdateGameObject(void)
{
	if (!offsetFg_)
	{
		Vector3 pos = transform_component_->GetPosition();
		transform_component_->SetPosition(pos.x - offset_.x, pos.y + offset_.y);
		offsetFg_ = true;
	}
}

