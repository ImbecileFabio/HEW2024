#include "TestObject.h"

TestObject::TestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"backdrop_03.png", 100);

}
TestObject::~TestObject(void)
{

}

void TestObject::UpdateGameObject(void)
{

}
