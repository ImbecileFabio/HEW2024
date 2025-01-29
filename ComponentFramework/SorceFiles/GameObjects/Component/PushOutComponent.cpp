//=================================================================
// [PushOutComponent.cpp] �����o���R���|�[�l���g
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�R���C�_�[�������Ă���ғ��m�������o���������s��
// 
//=================================================================
#include "PushOutComponent.h"

#include "../Component.h"
#include "../GameObject.h"

#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/TransformComponent.h"


//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
PushOutComponent::PushOutComponent(GameObject* _owner, int _updateOrder):
	Component(_owner, _updateOrder)
{
    this->Init();
}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
PushOutComponent::~PushOutComponent()
{
	this->Uninit();
}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void PushOutComponent::Init(void)
{
}

//-----------------------------------------------------------------
// �I������
//-----------------------------------------------------------------
void PushOutComponent::Uninit(void)
{
}

//-----------------------------------------------------------------
// @param _other �Փ˂����I�u�W�F�N�g
// @brief �����o���ʂ��v�Z���鏈��
//-----------------------------------------------------------------
void PushOutComponent::ResolveCollision(GameObject* _other) {

    auto myTransform = owner_->GetTransformComponent();
    auto myCollider = owner_->GetComponent<ColliderBaseComponent>();
    auto otherTransform = _other->GetTransformComponent();
    auto otherCollider = _other->GetComponent<ColliderBaseComponent>();

    auto myBoxCollider = dynamic_cast<BoxColliderComponent*>(myCollider);
    auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider);

    if (!myBoxCollider || !otherBoxCollider) {
        return;
    }
       // �ʒu���擾
    auto myPos = myTransform->GetPosition();
    auto otherPos = otherTransform->GetPosition();

    // �����Ƒ���� AABB ���擾
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();



    // �Փ˂��Ă��邩����
        if (myhitbox.max_.x > otherhitbox.min_.x &&
            myhitbox.min_.x < otherhitbox.max_.x &&
            myhitbox.max_.y > otherhitbox.min_.y &&
            myhitbox.min_.y < otherhitbox.max_.y)
        {
            // owner�̃T�C�Y���擾�i�����݂̂��g�p�j
            float ownerHeight = myhitbox.max_.y - myhitbox.min_.y;

            // �V�����ʒu���v�Z (���݈ʒu�� y ���T�C�Y�̔��������グ��)
            auto myPos = myTransform->GetPosition();
            myTransform->SetPosition({ myPos.x, otherhitbox.max_.y + ownerHeight / 2.0f, myPos.z });
        }
}
