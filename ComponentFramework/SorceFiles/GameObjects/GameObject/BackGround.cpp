#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{
		sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_02.png", 1);
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
