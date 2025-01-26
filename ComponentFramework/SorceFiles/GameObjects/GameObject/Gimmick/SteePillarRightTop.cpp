//=================================================================
// [SteePillarRightTop.cpp] 右鉄柱オブジェクトの一番上
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：右鉄柱オブジェクトの一番上実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarRightTop.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarRightTop::SteePillarRightTop(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRightTop")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillarRightTop::~SteePillarRightTop(void)
{
	delete sprite_component_;
	delete animation_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarRightTop::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
	//animation_component_ = new AnimationComponent(this, sprite_component_);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarRightTop::UpdateGameObject(void)
{

}

