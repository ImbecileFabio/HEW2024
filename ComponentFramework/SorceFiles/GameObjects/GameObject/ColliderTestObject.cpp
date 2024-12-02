#include "ColliderTestObject.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	: GameObject(_gameManager)
{
	this->InitGameObject();
}

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent_;
	delete colliderComponent_;
}


//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void ColliderTestObject::InitGameObject(void)
{
	this->spriteComponent_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	this->spriteComponent_->SetObjectName("Test");

	this->colliderComponent_ = new CircleColliderComponent(this, 100);

	this->transform_component_->SetScale(100.0f, 100.0f);
}

void ColliderTestObject::UpdateGameObject(void)
{
}
