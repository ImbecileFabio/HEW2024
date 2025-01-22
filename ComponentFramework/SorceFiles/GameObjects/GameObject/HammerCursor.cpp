//=================================================================
// [HammerCursor.cpp] 振り子を選択するカーソルソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：振り子を選択するカーソルの簡単な機能を実装
//=================================================================
/*----- インクルード -----*/
#include "HammerCursor.h"
#include "../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
HammerCursor::HammerCursor(GameManager* _gameManager)
	:GameObject(_gameManager, "HammerCursor")
	, sprite_component_		(nullptr)
	, hit_effect_component_	(nullptr)
	, animation_component_	(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
HammerCursor::~HammerCursor(void)
{
	delete sprite_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void HammerCursor::InitGameObject(void)
{
	sprite_component_	  = new SpriteComponent(this, "hammer");
	transform_component_->SetSize(100.0f, 100.0f);
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void HammerCursor::UpdateGameObject(void)
{
	// 描画切り替え
	if (isUiDraw)
		sprite_component_->SetState(RenderComponent::State::draw);
	else
		sprite_component_->SetState(RenderComponent::State::notDraw);

	//origin_pos_.x = origin_pos_.x;
	transform_component_->SetPosition(origin_pos_);
	//if (!isUiDraw)						// UIが非表示
	//{
	//	isUiDraw = true;
	//	isCursorMove = false;	// カーソルは動かさない
	//	sprite_component_->SetState(RenderComponent::State::notDraw);
	//}
	//else if (isUiDraw && !isCursorMove)	// UIが表示されている場合
	//{
	//	isCursorMove = true;
	//}
}