//==================================================
// [CircleColliderComponent.cpp] �~�̓����蔻���CPP�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F�~�̓����蔻��̃R���|�[�l���g
//==================================================
#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"
#include <iostream>
//--------------------------------------------------
// @brief �~�̓����蔻��̃R���X�g���N�^
//--------------------------------------------------
CircleColliderComponent::CircleColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
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
	auto transform = this->owner_->GetTransformComponent();
	if(transform)
	{
		this->circle_.position = transform->GetPosition();
		DirectX::SimpleMath::Vector3 size = transform->GetSize();
		this->circle_.radius = std::min<float>(size.x, size.y) / 2.0f;
	}
}
//--------------------------------------------------
// @brief �|���t�H�[���Y�����g���āA�R���|�[�l���g�œn���֐��𔻕ʂ��Ă����̑�ȃR�[�h
// @param _other ���N���X�̃R���|�[�l���g
// @return �������Ă��邩�ǂ���
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
//--------------------------------------------------
// @brief �~�Ɖ~�̓����蔻����Ƃ�֐�
// @param _other �~�̓����蔻��R���|�[�l���g
// @return �������Ă��邩�ǂ���
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	float dx = this->circle_.position.x - _other->GetCircleSize().position.x;
	float dy = this->circle_.position.y - _other->GetCircleSize().position.y;
	float distanceSquared = (dx * dx) + (dy * dy);
	float combinedRadius = this->circle_.radius + _other->GetCircleSize().radius;

	this->hitFg_ = distanceSquared <= (combinedRadius * combinedRadius);
	return this->hitFg_;
}
//--------------------------------------------------
// @brief �~�Ǝl�p�̓����蔻����Ƃ�֐�
// @param _other �l�p�̓����蔻��R���|�[�l���g
// @return �������Ă��邩�ǂ���
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto otherHitBox = _other->GetWorldHitBox();
	// �l�p�`���ŉ~�̒��S�ɍł��߂��_���v�Z
	float closestX =
		max(otherHitBox.min_.x, min(circle_.position.x, otherHitBox.max_.x));	// ���ƉE
	float closestY =
		max(otherHitBox.min_.y, min(circle_.position.y, otherHitBox.max_.y));	// ���Ə�
	// �ŋߓ_�Ɖ~�̒��S�̋������v�Z
	float distanceX = circle_.position.x - closestX;
	float distanceY = circle_.position.y - closestY;
	// ����
	if ((distanceX * distanceX) + (distanceY * distanceY) < (circle_.radius * circle_.radius))
	{
		this->hitFg_ = true;
		return true;
	}
	return false;
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