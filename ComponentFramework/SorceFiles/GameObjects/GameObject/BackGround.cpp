#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{
		sprite_component_ = new SpriteComponent(this, "backdrop_02", 0);
		this->InitGameObject();
}

BackGround::~BackGround(void)
{
	audio_manager_.Stop(SoundLabel_StageBGM);
	audio_manager_.Uninit();

	delete sprite_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void BackGround::InitGameObject(void)
{
	transform_component_->SetSize(2880, 1080);

	audio_manager_.Init();
	audio_manager_.SetVolume(SoundLabel_StageBGM, 1.0f);
	audio_manager_.SetCategoryVolume(BGM, 1.0f);
	audio_manager_.Play(SoundLabel_StageBGM);
}

void BackGround::UpdateGameObject(void)
{

}
