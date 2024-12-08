#include "ColliderTestObject.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	: GameObject(_gameManager, "ColliderTestObject")
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


//--------------------------------------------------
// ‰Šú‰»ˆ—
//--------------------------------------------------
void ColliderTestObject::InitGameObject(void)
{
	this->spriteComponent_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");

	this->colliderComponent_ = new CircleColliderComponent(this);

	this->transform_component_->SetScale(100.0f, 100.0f);
	this->transform_component_->SetRotation(60.0f);

	this->angVelCom_ = new AngularVelocityComponent(this);
	this->penCom_ = new PendulumMovementComponent(this);

}

void ColliderTestObject::UpdateGameObject(void)
{
	this->penCom_->PendulumAngle(0.01f);
	this->penCom_->PendulumPosition(Vector3(0.f, 0.f, 0.f), 200.f);
}
