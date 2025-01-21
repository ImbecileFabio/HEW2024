#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// @brief 振り子の棒のコンストラクタ
//--------------------------------------------------
Stick::Stick(GameManager* _gameManager, Pendulum* _pendulum)
	:GameObject(_gameManager, "Stick")
	, owner_pendulum_(_pendulum)
	, stick_length_state_(StickLengthState::Short)
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
	stick_length_state_ = StickLengthState::Middle;
}
//--------------------------------------------------
// @brief 振り子の棒の更新処理
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
	switch (stick_length_state_)
	{
	case StickLengthState::Short:
		transform_component_->SetSize(50.0f, 200.0f);
		break;
	case StickLengthState::Middle:
		transform_component_->SetSize(50.0f, 250.0f);
		break;
	case StickLengthState::Long:
		transform_component_->SetSize(50.0f, 300.0f);
		break;
	}

}
