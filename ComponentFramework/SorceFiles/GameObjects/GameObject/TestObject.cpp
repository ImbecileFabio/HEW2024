#include "TestObject.h"

TestObject::TestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{

	this->InitGameObject();

}

TestObject::~TestObject(void)
{
	delete sprite_component_;
}

//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void TestObject::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_03.png", 100);

	transform_component_->SetScale(1920, 1080);
}

void TestObject::UpdateGameObject(void)
{

}
