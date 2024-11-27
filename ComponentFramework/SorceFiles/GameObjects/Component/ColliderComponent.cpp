#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	testFg = false;
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
BoxColliderComponent::~BoxColliderComponent()
{
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̏���������
//--------------------------------------------------
void BoxColliderComponent::Init(void)
{
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̏I������
//--------------------------------------------------
void BoxColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̍X�V����
//--------------------------------------------------
void BoxColliderComponent::Update(void)
{
	this->position_ = this->owner_->	// GameObject�̍��W���擾
		GetTransformComponent()->GetPosition();
	DirectX::SimpleMath::Vector3 size = this->owner_->	// �T�C�Y���擾
		GetTransformComponent()->GetScale();
	this->boxSize_.w = position_.y + size.y / 2;	// ��	// �����蔻����X�V
	this->boxSize_.x = position_.y - size.y / 2;	// ��
	this->boxSize_.y = position_.x - size.x / 2;	// ��
	this->boxSize_.z = position_.x + size.x / 2;	// �E
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻�肪�d�Ȃ��Ă��邩�ǂ����̏���
// @param _other �����蔻����s������
// @return �d�Ȃ��Ă��邩�ǂ���
//--------------------------------------------------
void BoxColliderComponent::CheckCollision(const DirectX::SimpleMath::Vector4& _other)
{	
	// �E�ƍ�
	if (boxSize_.z < _other.y)
	{
		testFg = false; return;
	}
	// ���ƉE
	if (boxSize_.y > _other.z)
	{
		testFg = false; return;
	}
	// ���Ə�
	if (boxSize_.x > _other.w)
	{
		testFg = false; return;
	}
	// ��Ɖ�
	if (boxSize_.w < _other.x)
	{
		testFg = false; return;
	}
	std::cout << std::format("[BoxColliderComponent] -> CheckCollision\n");
	testFg = true;
}
//--------------------------------------------------
// @brief �~�̃R���X�g���N�^
//--------------------------------------------------
CircleColliderComponent::CircleColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	testFg = false;
}
//--------------------------------------------------
// @brief �~�̃f�X�g���N�^
//--------------------------------------------------
CircleColliderComponent::~CircleColliderComponent()
{
}
//--------------------------------------------------
// @brief �~�̓����蔻��̏���������
//--------------------------------------------------
void CircleColliderComponent::Init(void)
{
}
//--------------------------------------------------
// @brief �~�̓����蔻��̍X�V����
//--------------------------------------------------
void CircleColliderComponent::Update(void)
{
	DirectX::SimpleMath::Vector3 scale = this->owner_->GetTransformComponent()->GetScale();
	//this->circle_.radius = std::min<float>(scale.x, scale.y) / 2;
	this->circle_.radius = 16.0f / 2.0f;
	this->circle_.position = this->owner_->GetTransformComponent()->GetPosition();
}
//--------------------------------------------------
// @brief �~�̓����蔻��̏I������
//--------------------------------------------------
void CircleColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief �~�̓����蔻�肪�d�Ȃ��Ă��邩�ǂ����̏���
// @param _other �����蔻����s������
// @return �d�Ȃ��Ă��邩�ǂ���
//--------------------------------------------------
void CircleColliderComponent::CheckCollision(const CIRCLE& _other)
{
	float a = this->circle_.position.x - _other.position.x;
	float b = this->circle_.position.y - _other.position.y;
	float c = (a * a) + (b * b);	
	float sumRadius = this->circle_.radius + _other.radius;

	if (c <= sumRadius * sumRadius)
	{
		std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
		this->testFg = true;
		return;
	}
	//float a = std::pow((this->circle_.position.x - _other.position.x ), 2.0f);
	//float b = std::pow((this->circle_.position.y - _other.position.y ), 2.0f);
	//float c = a + b;	
	//float sumRadius = std::pow((this->circle_.radius + _other.radius) , 2.0f);
	//if (c < sumRadius)
	//{
	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
	//	this->testFg = true;
	//	return;
	//}
}
