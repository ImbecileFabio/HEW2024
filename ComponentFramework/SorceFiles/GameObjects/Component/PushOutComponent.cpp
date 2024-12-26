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
PushOutComponent::PushOutComponent(GameObject* _owner, int _updateOrder) :
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
		std::cout << "PushOutComponent::ResolveCollision -> BoxColliderComponent Not Found\n";
        return;
    }
       // �ʒu���擾
    auto myPos = myTransform->GetPosition();
    auto otherPos = otherTransform->GetPosition();

    // �����Ƒ���� AABB ���擾
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();

    // �y�l�g���[�V������
    DirectX::SimpleMath::Vector3 penetration;

    // �d�Ȃ�ʂ��v�Z
    float overlapX = min(myhitbox.max_.x, otherhitbox.max_.x) - max(myhitbox.min_.x, otherhitbox.min_.x);
    float overlapY = min(myhitbox.max_.y, otherhitbox.max_.y) - max(myhitbox.min_.y, otherhitbox.min_.y);

    if (overlapX <= 0.0f || overlapY <= 0.0f) { return; }


    // �ŏ��̏d�Ȃ�ʂ������o�������Ƃ��ĕԂ�
    if (overlapX < overlapY) {
        penetration = { overlapX * (myhitbox.min_.x < otherhitbox.min_.x ? -1.0f : 1.0f), 0.0f, 0.0f };
    }
    else {
        penetration = { 0.0f, overlapY * (myhitbox.min_.y < otherhitbox.min_.y ? -1.0f : 1.0f), 0.0f };
    }


    // �����̈ʒu�������o��
    myTransform->SetPosition(myPos + penetration);
}