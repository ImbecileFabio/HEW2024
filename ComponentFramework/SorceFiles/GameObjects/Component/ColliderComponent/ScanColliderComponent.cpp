//==================================================
// [ScanColliderComponent.cpp] 
// ���ҁF�L�n
//--------------------------------------------------
// �����F
//==================================================

#include "../../../TileMapManager.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "ScanColliderComponent.h"
#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
ScanColliderComponent::ScanColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
ScanColliderComponent::~ScanColliderComponent()
{
	this->Uninit();
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̏���������
//--------------------------------------------------
void ScanColliderComponent::Init(void)
{
	SetSize(TILE_SIZE_X, TILE_SIZE_Y);
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̏I������
//--------------------------------------------------
void ScanColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief �l�p�`�̓����蔻��̍X�V����
//--------------------------------------------------
void ScanColliderComponent::Update(void)
{
	auto pos = this->owner_->GetTransformComponent()->GetPosition();// �ʒu���擾
	this->SetWorldHitBox(pos);
}

bool ScanColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}

//--------------------------------------------------
// @brief �l�p�`���m�̓����蔻��
//--------------------------------------------------
bool ScanColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto myHitbox = this->GetWorldHitBox();		// ��
	auto otherHitbox = _other->GetWorldHitBox();	// ��
	// x����
	if (myHitbox.max_.x < otherHitbox.min_.x || myHitbox.min_.x > otherHitbox.max_.x) {
		this->hitFg_ = false;
		return false;
	}
	// y����
	if (myHitbox.max_.y < otherHitbox.min_.y || myHitbox.min_.y > otherHitbox.max_.y) {
		this->hitFg_ = false;
		return false;
	}

	// x, y�Ƃ��ɏd�Ȃ��Ă���
	this->hitFg_ = true;
	return true;
}
//--------------------------------------------------
// @brief �l�p�`�Ɖ~�̓����蔻��
//--------------------------------------------------
bool ScanColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
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
// @param _position owner�̒��S�ʒu
// @brief �����蔻��̍��W������
//--------------------------------------------------
void ScanColliderComponent::SetWorldHitBox(Vector3 _position)
{
	// �I�t�Z�b�g�K�p
	_position += offset_;

	world_hit_box_ = AABB{
		Vector2(_position.x - size_.x / 2, _position.y - size_.y / 2),		// ����
		Vector2(_position.x + size_.x / 2, _position.y + size_.y / 2)		// �E��
	};
}



