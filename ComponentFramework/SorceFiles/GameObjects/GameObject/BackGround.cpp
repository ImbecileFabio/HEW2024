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
// 初期化処理
//--------------------------------------------------
void BackGround::InitGameObject(void)
{
	transform_component_->SetSize(2880, 1080);
	sprite_component_->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
}

void BackGround::UpdateGameObject(void)
{

}
