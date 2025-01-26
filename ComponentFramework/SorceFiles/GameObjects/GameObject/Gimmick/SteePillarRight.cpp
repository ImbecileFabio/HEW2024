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
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarRight::SteePillarRight(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRight")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarRight::~SteePillarRight(void)
{
	delete sprite_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarRight::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarRight::UpdateGameObject(void)
{

}
//--------------------------------------------------
// @brief 所有されるグループの参照を設定
// @param _group[鉄柱グループ]
//--------------------------------------------------
void SteePillarRight::SetPillarRightGroup(SteePillarRightGroup* _group)
{
	stee_pillar_right_group_ = _group;
}

