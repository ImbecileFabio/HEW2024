//==================================================
// [BoxColliderComponent.cpp] �l�p�̓����蔻���CPP�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F�l�p�̓����蔻��̃R���|�[�l���g
//==================================================
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
BoxColliderComponent::~BoxColliderComponent()
{
	this->Uninit();
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
	auto pos = this->owner_->GetTransformComponent()->GetPosition();// �ʒu���擾
	this->SetWorldHitBox(pos);
}

bool BoxColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
//--------------------------------------------------
// @brief �l�p�`�Ɖ~�̓����蔻��
//--------------------------------------------------
bool BoxColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	auto myHitBox = this->GetWorldHitBox();			// ��
	auto circleSize = _other->GetCircleSize();	// ��
	// �l�p�`���ŉ~�̒��S�ɍł��߂��_���v�Z
	float closestX =
		max(myHitBox.min_.x, min(circleSize.position.x, myHitBox.max_.x));	// ���ƉE
	float closestY =
		max(myHitBox.min_.y, min(circleSize.position.y, myHitBox.max_.y));	// ���Ə�
	// �ŋߓ_�Ɖ~�̒��S�̋������v�Z
	float distanceX = circleSize.position.x - closestX;
	float distanceY = circleSize.position.y - closestY;
	// ����
	if ((distanceX * distanceX) + (distanceY * distanceY) < (circleSize.radius * circleSize.radius))
	{
		this->hitFg_ = true;
		return true;
	}
	return false;
}

//--------------------------------------------------
// @brief �l�p�`���m�̓����蔻��
//--------------------------------------------------
bool BoxColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto myHitbox    = this->GetWorldHitBox();		// ��
	auto otherHitbox = _other->GetWorldHitBox();	// ��
	// x����
	if ( myHitbox.max_.x < otherHitbox.min_.x || myHitbox.min_.x > otherHitbox.max_.x) {
		this->hitFg_ = false;
		return false;
	}
	// y����
	if(myHitbox.max_.y < otherHitbox.min_.y || myHitbox.min_.y > myHitbox.max_.y){
		this->hitFg_ = false;
		return false;
	}

	// x, y�Ƃ��ɏd�Ȃ��Ă���
	this->hitFg_ = true;
	return true;
}

//--------------------------------------------------
// @param _position owner�̒��S�ʒu
// @brief �����蔻��̍��W������
//--------------------------------------------------
void BoxColliderComponent::SetWorldHitBox(Vector3 _position)
{
	// �I�t�Z�b�g�K�p
	_position += offset_;

	hit_box_ = AABB{
		Vector2(_position.x - size_.x / 2, _position.y - size_.y / 2),		// ����
		Vector2(_position.x + size_.x / 2, _position.y + size_.y / 2)		// �E��
	};
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
