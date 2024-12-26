#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{

	this->InitGameObject();

}

BackGround::~BackGround(void)
{
	sound_.Stop(SoundLabel_TitleBGM);
	sound_.Uninit();
	delete sprite_component_;
}

//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void BackGround::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_02.png", 100);

	transform_component_->SetScale(2880, 1080);

	sound_.Init();
	sound_.Play(SoundLabel_TitleBGM);
}

void BackGround::UpdateGameObject(void)
{

}
