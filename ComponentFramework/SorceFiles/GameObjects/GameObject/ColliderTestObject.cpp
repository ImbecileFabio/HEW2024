#include "ColliderTestObject.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RigidbodyComponent/AngularVelocityComponent.h"
#include "../Component/PendulumMovementComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	: GameObject(_gameManager)
{
	this->InitGameObject();
}

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent_;
	delete colliderComponent_;
	delete angVelCom_;
	delete penCom_;
}
void ColliderTestObject::InitGameObject(void)
{
	this->spriteComponent_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	this->spriteComponent_->SetObjectName("Test");

	this->colliderComponent_ = new CircleColliderComponent(this, 100);

	this->transform_component_->SetScale(100.0f, 100.0f);

	// ペンデュラムの動きのテスト
	this->angVelCom_ = new AngularVelocityComponent(this);
	this->penCom_ = new PendulumMovementComponent(this);
	this->penCom_->SetPendulumAngle(60.f);
	

}
void ColliderTestObject::UpdateGameObject(void)
{
	this->penCom_->Update(0.01f, Vector3(0.f, 0.f, 0.f), 200.f);
}
