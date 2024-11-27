#include "ColliderTestObject.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	spriteComponent = new SpriteComponent(this, TEXTURE_PATH_"Ball.png");
	spriteComponent->SetObjectName("Test");

	circleColliderComponent = new CircleColliderComponent(this, 100);

	transform_component_->SetScale( 1, 1);
}

//Perspective=“§‹“Š‰e
//Ortho~=•½s“Š‰e

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent;
	delete circleColliderComponent;
}
void ColliderTestObject::UpdateGameObject(void)
{
}
