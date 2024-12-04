#include "ColliderTestObject.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	: GameObject(_gameManager)
{
	this->spriteComponent_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	this->spriteComponent_->SetObjectName("Test");

	this->colliderComponent_ = new CircleColliderComponent(this, 100);

	this->transform_component_->SetScale(100.0f, 100.0f);
}

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent_;
	delete colliderComponent_;
}
void ColliderTestObject::UpdateGameObject(void)
{
}
/*とりあえずテスト用のEnterだけ*/
void ColliderTestObject::OnCollisionEnter2D(GameObject& _other)
{
	std::cout << std::format("[ColliderTestObject] -> OnCollisionEnter2D Start\n");
}
