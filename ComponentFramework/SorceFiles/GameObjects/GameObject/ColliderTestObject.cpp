#include "ColliderTestObject.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _colliderManager)
	:GameObject(_colliderManager)
{
	spriteComponent = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	spriteComponent->SetObjectName("Test");

	colliderComponent = new CircleColliderComponent(this, 100);

	transform_component_->SetScale(100.0f, 100.0f);
}

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent;
	delete colliderComponent;
}
void ColliderTestObject::UpdateGameObject(void)
{
}
