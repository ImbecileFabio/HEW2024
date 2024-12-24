#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
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
	delete pendulum_component_;
}
//--------------------------------------------------
// @brief 振り子の棒の初期化処理
//--------------------------------------------------
void Stick::InitGameObject(void)
{
	sprite_component_	= new SpriteComponent(this, TEXTURE_PATH_"huriko/v02/stick_01.png");
	transform_component_->SetSize(100.0f, 300.0f);
}
//--------------------------------------------------
// @brief 振り子の棒の更新処理
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
}
