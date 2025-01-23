#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{
		sprite_component_ = new SpriteComponent(this, "backdrop_02", 0);
		this->InitGameObject();
}

BackGround::~BackGround(void)
{
	delete sprite_component_;
}

//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void BackGround::InitGameObject(void)
{
	transform_component_->SetSize(2880, 1080);
}

void BackGround::UpdateGameObject(void)
{

}
