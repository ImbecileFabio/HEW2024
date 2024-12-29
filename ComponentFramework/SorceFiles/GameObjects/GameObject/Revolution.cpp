#include "Revolution.h"
#include "../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Revolution::Revolution(GameManager* _gameManager, const std::string _imgName)
	: GameObject(_gameManager, "Revolution")
{
	sprite_component_ = new SpriteComponent(this, _imgName, 0);
	sound_.Init();
	sound_.Play(SoundLabel_TitleBGM);
	this->InitGameObject();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Revolution::~Revolution()
{
	delete sprite_component_;
	sound_.Stop(SoundLabel_TitleBGM);
	sound_.Uninit();
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Revolution::InitGameObject()
{

}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Revolution::UpdateGameObject()
{
}
