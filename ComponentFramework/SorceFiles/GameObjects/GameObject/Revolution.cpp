#include "Revolution.h"
#include "../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Revolution::Revolution(GameManager* _gameManager, const std::string _imgName, int _drawOrder)
	: GameObject(_gameManager, "Revolution")
{
	sprite_component_ = new SpriteComponent(this, _imgName, _drawOrder);
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
