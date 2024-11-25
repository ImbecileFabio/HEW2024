#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
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
	// �Ƃ肠�����z��ʂ�̐}�`���ł邩�ǂ����̃e�X�g
	// ���������I�u�W�F�N�g������W�������Ă���
	position_ = owner_->GetComponent<TransformComponent>()->GetPosition();
	DirectX::SimpleMath::Vector3 size = owner_->GetComponent<TransformComponent>()->GetScale();

	boxSize_.w = position_.y + size.y / 2;	// ��
	boxSize_.x = position_.y - size.y / 2;	// ��
	boxSize_.y = position_.x - size.x / 2;	// ��
	boxSize_.z = position_.x + size.x / 2;	// �E
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
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻�肪�d�Ȃ��Ă��邩�ǂ����̏���
// @param _collider �����蔻����s������
// @return �d�Ȃ��Ă��邩�ǂ���
//--------------------------------------------------
bool BoxColliderComponent::CheckCollision(const BoxColliderComponent* _collider) const
{
	DirectX::SimpleMath::Vector4 other = _collider->boxSize();	// ����̓����蔻��̃T�C�Y���擾
	if (boxSize_.w < other.x || boxSize_.x > other.w || boxSize_.y > other.z || boxSize_.z < other.y)
	{	// �d�Ȃ�����
		return true;
	}
	return false;
}
