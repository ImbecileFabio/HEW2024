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
	, is_robot_(true)	// ���{�b�g���ǂ���
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
	auto ownerVelocityCom = owner_->GetComponent<VelocityComponent>();
	if (!ownerVelocityCom) return;

	// �n�ʔ���̍X�V
	bool wasGrounded = is_ground_;
	if (is_robot_)
	{
		CheckGroundCollision();
	}

	// �d�͂̓K�p
	if (use_gravity_)
	{
		if (!is_ground_)  //�󒆂ɂ���ꍇ
		{
			Vector3 currentVel = ownerVelocityCom->GetVelocity();

			// �������x����
			const float maxFallSpeed = -10.0f;
			if (currentVel.y <= maxFallSpeed)
			{
				currentVel.y = maxFallSpeed;
			}
			else
			{
				currentVel.y += gravity_;
			}

			ownerVelocityCom->SetVelocity(currentVel);
		}
	}
}



//--------------------------------------------------
// @brief �n�ʂƂ̓����蔻��
// @return �n�ʂɐڂ��Ă���: true, �n�ʂɐڂ��Ă��Ȃ�: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollision()
{
    auto boxCollider = owner_->GetComponent<BoxColliderComponent>();
    if (!boxCollider) return false;

    auto hitbox = boxCollider->GetWorldHitBox();
    AABB groundCheckHitbox = hitbox;

    const float checkOffset = 0.1f;  // �n�ʔ���̃I�t�Z�b�g
    const float checkHeight = 4.0f;  // �n�ʔ���̍����͈�

    // �����̃X�L�����͈͂𐳂����ݒ�
    groundCheckHitbox.min_.y = hitbox.min_.y - checkOffset;  // ���݈ʒu���班����
    groundCheckHitbox.max_.y = hitbox.min_.y + checkHeight;  // ������܂�

    auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

    // �n�ʂƂ̓����蔻��
    for (const auto& obj : objects)
    {
        // ���菜�O
        if (obj == owner_) continue;
        if (obj->GetType() == GameObject::TypeID::Item) continue;

        auto otherCollider = obj->GetComponent<BoxColliderComponent>();
        if (!otherCollider) continue;

        auto otherHitbox = otherCollider->GetWorldHitBox();

        // AABB���m�̏Փ˔���
        if (groundCheckHitbox.max_.x > otherHitbox.min_.x &&
            groundCheckHitbox.min_.x < otherHitbox.max_.x &&
            groundCheckHitbox.max_.y > otherHitbox.min_.y &&
            groundCheckHitbox.min_.y < otherHitbox.max_.y)
        {
            // Y�������̊ђʐ[�x���v�Z
            float penetrationDepth = otherHitbox.max_.y - groundCheckHitbox.min_.y;

            // �K�؂Ȑڒn����
            if (penetrationDepth >= 0.0f && penetrationDepth <= checkOffset + checkHeight)
            {
                is_ground_ = true;

                // �ڒn���ɑ��x�����Z�b�g
                if (auto vel = owner_->GetComponent<VelocityComponent>())
                {
                    Vector3 currentVel = vel->GetVelocity();
                    if (currentVel.y < 0)  // ���~���̏ꍇ�̂�
                    {
                        vel->SetVelocity(Vector3(currentVel.x, 0.0f, currentVel.z));
                    }
                }

                return true;
            }
        }
    }

    is_ground_ = false;
    return false;
}