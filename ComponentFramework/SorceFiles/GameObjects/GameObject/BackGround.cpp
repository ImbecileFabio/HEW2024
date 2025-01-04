#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{
		sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_02.png", 1);
		this->InitGameObject();
}

BackGround::~BackGround(void)
{
	sound_.Stop(SoundLabel_StageBGM);
	sound_.Uninit();

	delete sprite_component_;
}

//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void BackGround::InitGameObject(void)
{
	transform_component_->SetSize(2880, 1080);

	sound_.Init();
	sound_.Play(SoundLabel_StageBGM);
}

void BackGround::UpdateGameObject(void)
{

}
