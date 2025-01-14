#include "BackGround.h"

BackGround::BackGround(GameManager* _gameManager)
	:GameObject(_gameManager, "BackGround")
{
		sprite_component_ = new SpriteComponent(this, "backdrop_02", 0);
		this->InitGameObject();
}

BackGround::~BackGround(void)
{
	sound_.Stop(SoundLabel_StageBGM);
	sound_.Uninit();

	delete sprite_component_;
}

//--------------------------------------------------
// 初期化処理
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
