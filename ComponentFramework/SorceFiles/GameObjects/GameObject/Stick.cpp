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
	stick_move_component_ = new StickMoveComponent(this, owner_pendulum_);
	sprite_component_	= new SpriteComponent(this, "stick", 30);
	stick_length_state_ = StickLengthState::Middle;
}
//--------------------------------------------------
// @brief 振り子の棒の更新処理
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
	
	// 振り子の球の状態によってstateが変わる
	switch (stick_length_state_)
	{
	case StickLengthState::Short:

		break;
	case StickLengthState::Middle:

		break;
	case StickLengthState::Long:

		break;
	}


	// 棒の状態をコンポーネントに反映する
	stick_move_component_->SetLengthState(static_cast<StickMoveComponent::LengthState>(stick_length_state_));


}
