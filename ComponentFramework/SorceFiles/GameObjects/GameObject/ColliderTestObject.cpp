#include "ColliderTestObject.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"

ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	: GameObject(_gameManager)
{
	this->spriteComponent_ = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	this->spriteComponent_->SetObjectName("Test");

	this->colliderComponent_ = new CircleColliderComponent(this, 100);

	this->transform_component_->SetScale(100.0f, 100.0f);
	this->GetComponent<TransformComponent>()->SetRotation(60.f);
	this->angVelCom_ = new AngularVelocityComponent(this);
	this->penCom_ = new PendulumMovementComponent(this);
}

ColliderTestObject::~ColliderTestObject()
{
	delete spriteComponent_;
	delete colliderComponent_;
	delete angVelCom_;
	delete penCom_;
}
void ColliderTestObject::UpdateGameObject(void)
{
	this->penCom_->PendulumAngle(0.01f);
	this->penCom_->PendulumPosition(Vector3(0.f, 0.f, 0.f), 200.f);
}
/*とりあえずテスト用のEnterだけ*/
void ColliderTestObject::OnCollisionEnter2D(GameObject& _other)
{

}
