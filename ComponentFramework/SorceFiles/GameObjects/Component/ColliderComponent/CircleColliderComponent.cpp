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
	this->circle_.position = this->owner_->GetComponent<TransformComponent>()->GetPosition();
	DirectX::SimpleMath::Vector3 scale =
		this->owner_->GetComponent<TransformComponent>()->GetScale();
	this->circle_.radius = std::min<float>(scale.x, scale.y) / 2.0f;
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
	float a = this->circle_.position.x - _other->GetCircleSize().position.x;
	float b = this->circle_.position.y - _other->GetCircleSize().position.y;
	float c = (a * a) + (b * b);
	float sumRadius = this->circle_.radius + _other->GetCircleSize().radius;

	if (c <= sumRadius * sumRadius)
	{
		this->hitFg_ = true;
		return true;
	}
	this->hitFg_ = false;  return false;
}
//--------------------------------------------------
// @brief �~�Ǝl�p�̓����蔻����Ƃ�֐�
// @param _other �l�p�̓����蔻��R���|�[�l���g
// @return �������Ă��邩�ǂ���
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto boxSize = _other->GetBoxSize();
	// �l�p�`���ŉ~�̒��S�ɍł��߂��_���v�Z
	float closestX =
		max(boxSize.y, min(circle_.position.x, boxSize.z));	// ���ƉE
	float closestY =
		max(boxSize.x, min(circle_.position.y, boxSize.w));	// ���Ə�
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