#include "TestObject.h"

TestObject::TestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_03.png", 100);

	transform_component_->SetScale(1920, 1080);
}
TestObject::~TestObject(void)
{
}

void TestObject::UpdateGameObject(void)
{
}
