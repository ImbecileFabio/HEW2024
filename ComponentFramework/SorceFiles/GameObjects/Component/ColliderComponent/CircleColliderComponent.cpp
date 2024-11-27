#include "CircleColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief �~�̓����蔻��̃R���X�g���N�^
//--------------------------------------------------
CircleColliderComponent::CircleColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
	testFg = false;
}
//--------------------------------------------------
// @brief  �~�̓����蔻��̃f�X�g���N�^
//--------------------------------------------------
CircleColliderComponent::~CircleColliderComponent()
{
}
//--------------------------------------------------
// @brief  �~�̓����蔻��̏���������
//--------------------------------------------------
void CircleColliderComponent::Init(void)
{
}
//--------------------------------------------------
// @brief �~�̓����蔻��̍X�V����
//--------------------------------------------------
void CircleColliderComponent::Update(void)
{
	DirectX::SimpleMath::Vector3 scale =
		this->owner_->GetComponent<TransformComponent>()->GetScale();
	this->circle_.radius = std::min<float>(scale.x, scale.y) / 2;
	this->circle_.position = 
		this->owner_->GetComponent<TransformComponent>()->GetPosition();
}
//--------------------------------------------------
// @brief �~�̓����蔻��̏I������
//--------------------------------------------------
void CircleColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief �~�̓����蔻����Ƃ�֐�
// @param _other �~�̍��W�Ɣ��a
//--------------------------------------------------
//void CircleColliderComponent::CheckCollision(const CIRCLE& _other)
//{
//	//float a = this->circle_.position.x - _other.position.x;
//	//float b = this->circle_.position.y - _other.position.y;
//	//float c = (a * a) + (b * b);
//	//float sumRadius = this->circle_.radius + _other.radius;
//
//	//if (c <= sumRadius * sumRadius)
//	//{
//	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
//	//	this->testFg = true;
//	//	return;
//	//}
//	//float a = std::pow((this->circle_.position.x - _other.position.x ), 2.0f);
//	//float b = std::pow((this->circle_.position.y - _other.position.y ), 2.0f);
//	//float c = a + b;	
//	//float sumRadius = std::pow((this->circle_.radius + _other.radius) , 2.0f);
//	//if (c < sumRadius)
//	//{
//	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
//	//	this->testFg = true;
//	//	return;
//	//}
//}