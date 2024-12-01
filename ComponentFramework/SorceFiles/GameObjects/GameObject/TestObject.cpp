#include "TestObject.h"

TestObject::TestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"icon.png", 100);

	transform_component_->SetScale(100, 100);

}
TestObject::~TestObject(void)
{

}

void TestObject::UpdateGameObject(void)
{

}
