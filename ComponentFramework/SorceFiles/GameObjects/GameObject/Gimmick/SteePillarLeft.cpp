//=================================================================
// [SteePillarLeft.cpp] 鉄柱オブジェクトのCPP
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱オブジェクトの実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarLeft.h"
#include "../Gimmick/Group/SteePillarLeftGroup.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarLeft::SteePillarLeft(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeft")
	, sprite_component_(nullptr)
	, offset_(0.0f, 0.0f)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarLeft::~SteePillarLeft(void)
{
	delete sprite_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarLeft::InitGameObject(void)
{
	offset_ = {11.0f, 0.0f };
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarLeft::UpdateGameObject(void)
{
	if (!offsetFg_)
	{
		Vector3 pos = transform_component_->GetPosition();
		transform_component_->SetPosition(pos.x - offset_.x, pos.y + offset_.y);
		offsetFg_ = true;
	}
}
//--------------------------------------------------
// @brief 左鉄柱グループの参照を設定
// @param _group[左鉄柱グループ]
//--------------------------------------------------
void SteePillarLeft::SetPillarLeftGroup(SteePillarLeftGroup* _group)
{
	stee_pillar_left_group_ = _group;
}

