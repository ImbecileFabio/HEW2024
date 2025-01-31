#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// @brief U‚èŽq‚Ì–_‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
//--------------------------------------------------
Stick::Stick(GameManager* _gameManager, Pendulum* _pendulum)
	:GameObject(_gameManager, "Stick")
	, owner_pendulum_(_pendulum)
	, stick_length_state_(StickLengthState::Short)
{
	InitGameObject();
}
//--------------------------------------------------
// @brief U‚èŽq‚Ì–_‚ÌƒfƒXƒgƒ‰ƒNƒ^
//--------------------------------------------------
Stick::~Stick()
{
	delete sprite_component_;
	delete stick_move_component_;
}
//--------------------------------------------------
// @brief U‚èŽq‚Ì–_‚Ì‰Šú‰»ˆ—
//--------------------------------------------------
void Stick::InitGameObject(void)
{
	stick_move_component_ = new StickMoveComponent(this, owner_pendulum_);
	sprite_component_	= new SpriteComponent(this, "stick", 30);
	stick_length_state_ = StickLengthState::Middle;
}
//--------------------------------------------------
// @brief U‚èŽq‚Ì–_‚ÌXVˆ—
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
	
	// U‚èŽq‚Ì‹…‚Ìó‘Ô‚É‚æ‚Á‚Ästate‚ª•Ï‚í‚é
	switch (stick_length_state_)
	{
	case StickLengthState::Short:

		break;
	case StickLengthState::Middle:

		break;
	case StickLengthState::Long:

		break;
	}


	// –_‚Ìó‘Ô‚ðƒRƒ“ƒ|[ƒlƒ“ƒg‚É”½‰f‚·‚é
	stick_move_component_->SetLengthState(static_cast<StickMoveComponent::LengthState>(stick_length_state_));


}
