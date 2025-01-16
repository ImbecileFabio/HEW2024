#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// @brief 振り子の棒のコンストラクタ
//--------------------------------------------------
Stick::Stick(GameManager* _gameManager)
	:GameObject(_gameManager, "Stick")
{
	InitGameObject();
}
//--------------------------------------------------
// @brief 振り子の棒のデストラクタ
//--------------------------------------------------
Stick::~Stick()
{
	delete sprite_component_;
	delete stick_move_component_;
}
//--------------------------------------------------
// @brief 振り子の棒の初期化処理
//--------------------------------------------------
void Stick::InitGameObject(void)
{
	stick_move_component_ = new StickMoveComponent(this);
	sprite_component_	= new SpriteComponent(this, "stick", 9);
	transform_component_->SetSize(50.0f, 200.0f);
}
//--------------------------------------------------
// @brief 振り子の棒の更新処理
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
}
