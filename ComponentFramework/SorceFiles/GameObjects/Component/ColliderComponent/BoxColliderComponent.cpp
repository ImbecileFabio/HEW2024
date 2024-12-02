#include "BoxColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
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
	this->position_ = this->owner_->GetComponent<TransformComponent>()->GetPosition();	// �ʒu���擾
	DirectX::SimpleMath::Vector3 size = this->owner_->GetComponent<TransformComponent>()->GetScale();	// �T�C�Y���擾
	this->boxSize_.w = position_.y + size.y / 2;	// ��	// �����蔻����X�V
	this->boxSize_.x = position_.y - size.y / 2;	// ��
	this->boxSize_.y = position_.x - size.x / 2;	// ��
	this->boxSize_.z = position_.x + size.x / 2;	// �E
}
bool BoxColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
bool BoxColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	return false;
}
bool BoxColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	// �E�ƍ�
	if (boxSize_.z < _other->GetBoxSize().y)
	{
		return false;
	}
	// ���ƉE
	if (boxSize_.y > _other->GetBoxSize().z)
	{
		return false;
	}
	// ���Ə�
	if (boxSize_.x > _other->GetBoxSize().w)
	{
		return false;
	}
	// ��Ɖ�
	if (boxSize_.w < _other->GetBoxSize().x)
	{
		return false;
	}
	return true;
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻�肪�d�Ȃ��Ă��邩�ǂ����̏���
// @param _other �����蔻����s������
// @return �d�Ȃ��Ă��邩�ǂ���
//--------------------------------------------------
//void BoxColliderComponent::CheckCollision(const DirectX::SimpleMath::Vector4& _other)
//{
//	// �E�ƍ�
//	if (boxSize_.z < _other.y)
//	{
//		testFg = false; return;
//	}
//	// ���ƉE
//	if (boxSize_.y > _other.z)
//	{
//		testFg = false; return;
//	}
//	// ���Ə�
//	if (boxSize_.x > _other.w)
//	{
//		testFg = false; return;
//	}
//	// ��Ɖ�
//	if (boxSize_.w < _other.x)
//	{
//		testFg = false; return;
//	}
//	testFg = true;
//}
