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
	, is_ground_(false)	// �n�ʂɐڒn���Ă��邩
	, is_robot_ (true)	// ���{�b�g���ǂ���
	, use_gravity_(true)	// �d�͂̎g�p
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
	if (auto ownerVelocityCom = owner_->GetComponent<VelocityComponent>())
	{
		if (!is_robot_ && use_gravity_)
		{
			// ���x�����ȏ�ɂȂ�Ȃ��悤�ɐ���
			if (ownerVelocityCom->GetVelocity().y < -10.0f)
			{
				ownerVelocityCom->SetVelocity({ 0.0f, -10.0f, 0.0f });
			}
			else
			{
				ownerVelocityCom->SetVelocity({ 0.0f, ownerVelocityCom->GetVelocity().y + gravity_, 0.0f });
			}
			return;
		}
		if (is_robot_)
		{
			CheckGroundCollision();
		}
		// �d�͓K�p
		if (use_gravity_ && !is_ground_ && is_robot_)
		{
			// ���x�����ȏ�ɂȂ�Ȃ��悤�ɐ���
			if (ownerVelocityCom->GetVelocity().y < -10.0f)
			{
				ownerVelocityCom->SetVelocity({ 0.0f, -10.0f, 0.0f });
			}
			else
			{
				ownerVelocityCom->SetVelocity({ 0.0f, ownerVelocityCom->GetVelocity().y + gravity_, 0.0f });
			}
		}
	}
}



//--------------------------------------------------
// @brief �n�ʂƂ̓����蔻��
// @return �n�ʂɐڂ��Ă���: true, �n�ʂɐڂ��Ă��Ȃ�: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollision()
{
	auto robotHitbox = owner_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
	AABB groundCheckHitbox = robotHitbox;

	// �����̃X�L�����͈͂�ݒ�i�L�����N�^�[�T�C�Y�ɉ����Ē����j
	float groundCheckHeight = (robotHitbox.max_.y - robotHitbox.min_.y) * 0.02;
	groundCheckHitbox.min_.y -= groundCheckHeight; // �����������ɔ͈͂��쐬
	groundCheckHitbox.max_.y = robotHitbox.min_.y;
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

	// �n�ʂƂ̓����蔻��
	for (const auto& obj : objects)
	{
		if (obj == owner_) continue; // �������g�Ƃ̔���̓X�L�b�v
		else if (obj->GetType() == GameObject::TypeID::Item) continue; // ���Ԃł��������Ⴄ�̂Ŗ���
		//else if (obj->GetType() == GameObject::TypeID::Smoke) continue; // ���Ԃł��������Ⴄ�̂Ŗ���
		//else if (obj->GetType() == GameObject::TypeID::SmokePipe) continue; // ���Ԃł��������Ⴄ�̂Ŗ���

		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			if (groundCheckHitbox.max_.x > otherHitbox.min_.x && groundCheckHitbox.min_.x < otherHitbox.max_.x &&
				groundCheckHitbox.max_.y > otherHitbox.min_.y && groundCheckHitbox.min_.y < otherHitbox.max_.y) {
				is_ground_ = true; // �n�ʂɐڂ��Ă���
				return true; // �n�ʂɐڂ��Ă���
			}
		}
	}

	is_ground_ = false; // �n�ʂɐڂ��Ă��Ȃ�
	return false; // �n�ʂɐڂ��Ă��Ȃ�
}
