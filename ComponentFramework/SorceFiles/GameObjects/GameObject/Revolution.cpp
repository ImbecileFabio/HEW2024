#include "Revolution.h"
#include "../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Revolution::Revolution(GameManager* _gameManager, const std::string _imgName)
	: GameObject(_gameManager, "Revolution")
{
	sprite_component_ = new SpriteComponent(this, _imgName, 0);
	this->InitGameObject();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Revolution::~Revolution()
{
	delete sprite_component_;
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
