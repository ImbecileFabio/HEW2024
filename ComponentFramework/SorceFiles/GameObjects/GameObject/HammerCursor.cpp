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
	, direction_(1)
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
	isUiDraw_ = true;
	sprite_component_	  = new SpriteComponent(this, "hammer", 3);
	transform_component_->SetSize(50.0f, 50.0f);
	transform_component_->SetRotation(-13.0f);
	transform_component_->SetPosition(-2000.0f, 0.0f);
	offset_ = { 45.0f, -10.0f };
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void HammerCursor::UpdateGameObject(void)
{
	// 描画切り替え
	if (isUiDraw_)
		sprite_component_->SetState(RenderComponent::State::draw);
	else
		sprite_component_->SetState(RenderComponent::State::notDraw);

}
void HammerCursor::HammerCursorMove()
{
	if (direction_ == -1)
	{
		transform_component_->SetRotation(-13.0f);
		origin_pos_ += offset_;
	}
	else if (direction_ == 1)
	{
		transform_component_->SetRotation(-12.0f);
		origin_pos_.x -= offset_.x;
		origin_pos_.y += offset_.y;
	}
	transform_component_->SetPosition(origin_pos_);
}