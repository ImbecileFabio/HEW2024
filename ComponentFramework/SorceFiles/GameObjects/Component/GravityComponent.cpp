//==================================================
// [GravityComponent.cpp] �d�̓R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�d�͂𐧌䂷��R���|�[�l���g
//==================================================
/*----- �C���N���[�h -----*/
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../GameObject.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
#include "GravityComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
GravityComponent::GravityComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, gravity_(-1.0f)	// �d��
{
	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
GravityComponent::~GravityComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void GravityComponent::Init()
{
	velocity_ = nullptr;
	collider_ = nullptr;
	is_ground_ = false;
	use_gravity_ = true;
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void GravityComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void GravityComponent::Update()
{
	if (!velocity_ || !collider_)	//	��x�����擾
	{
	velocity_ = this->owner_->GetComponent<VelocityComponent>();
	collider_ = this->owner_->GetComponent<BoxColliderComponent>();
	}

	// �n��ɋ��Ă邩
	is_ground_ = CheckGroundCollishion();

	use_gravity_ = !is_ground_;

	// �d�͓K�p
	if (use_gravity_)	
	{
		velocity_->SetVelocity(Vector3(0.0f, gravity_, 0.0f));
	}

}



//--------------------------------------------------
// @brief �n�ʂƂ̓����蔻��
// @return �n�ʂɐڂ��Ă���: true, �n�ʂɐڂ��Ă��Ȃ�: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollishion()
{
	auto robotHitbox = collider_->GetWorldHitBox();
	AABB groundCheckHitbox = robotHitbox;

	// �����Ƀ`�F�b�N������쐬
	groundCheckHitbox.min_.y -= 1.0f;
	groundCheckHitbox.max_.y = robotHitbox.min_.y;

	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

	// �n�ʂƂ̓����蔻��
	for (const auto& obj : objects)
	{
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			if (groundCheckHitbox.max_.x > otherHitbox.min_.x && groundCheckHitbox.min_.x < otherHitbox.max_.x &&
				groundCheckHitbox.max_.y > otherHitbox.min_.y && groundCheckHitbox.min_.y < otherHitbox.max_.y) {
				return true; // �n�ʂɐڂ��Ă���
			}
		}
	}

	return false; // �n�ʂɐڂ��Ă��Ȃ�
}
