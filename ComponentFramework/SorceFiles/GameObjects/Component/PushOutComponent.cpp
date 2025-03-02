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
#include "../Component/GimmickComponent/LiftInteractionComponent.h"


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

    // ���t�g�ɏ���Ă���ꍇ�͉������̉����o���݂̂��s��
    auto liftInteraction = owner_->GetComponent<LiftInteractionComponent>();
    bool isOnLift = liftInteraction && liftInteraction->GetLift() != nullptr;

    auto myTransform = owner_->GetTransformComponent();
    auto myCollider = owner_->GetComponent<ColliderBaseComponent>();
    auto otherTransform = _other->GetTransformComponent();
    auto otherCollider = _other->GetComponent<ColliderBaseComponent>();

    auto myBoxCollider = dynamic_cast<BoxColliderComponent*>(myCollider);
    auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider);

    if (!myBoxCollider || !otherBoxCollider) {
        return;
    }

    // AABB ���擾
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();

    // �Փ˔���
    if (myhitbox.max_.x > otherhitbox.min_.x &&
        myhitbox.min_.x < otherhitbox.max_.x &&
        myhitbox.max_.y > otherhitbox.min_.y &&
        myhitbox.min_.y < otherhitbox.max_.y)
    {
        // �Փ˂̐[�����v�Z
        float overlapX = min(myhitbox.max_.x - otherhitbox.min_.x, otherhitbox.max_.x - myhitbox.min_.x);
        float overlapY = min(myhitbox.max_.y - otherhitbox.min_.y, otherhitbox.max_.y - myhitbox.min_.y);

        // ���t�g�ɏ���Ă���ꍇ�͐��������̉����o�����X�L�b�v
        if (isOnLift && overlapX > overlapY) {
            return;
        }

        // X��Y�ǂ���̏Փ˂��[�����𔻒�
        if (overlapX < overlapY) {
            // �������̕␳�i���E�̉����o���j
            if (myhitbox.min_.x < otherhitbox.min_.x) {
                myTransform->SetPosition({
                    otherhitbox.min_.x - (myhitbox.max_.x - myhitbox.min_.x) / 2.0f,
                    myTransform->GetPosition().y,
                    myTransform->GetPosition().z });
            }
            else {
                myTransform->SetPosition({
                    otherhitbox.max_.x + (myhitbox.max_.x - myhitbox.min_.x) / 2.0f,
                    myTransform->GetPosition().y,
                    myTransform->GetPosition().z });
            }
        }
        else if(!isOnLift){
            // �c�����̕␳�i��܂��͉�����̉����o���j
            if (myhitbox.min_.y < otherhitbox.min_.y) {
                // �ォ�瓖�����Ă���ꍇ �� ���̏�ɕ␳
                myTransform->SetPosition({ myTransform->GetPosition().x, otherhitbox.min_.y - (myhitbox.max_.y - myhitbox.min_.y) / 2.0f, myTransform->GetPosition().z });
            }
            else {
                // �����瓖�����Ă���ꍇ �� ���̉��ɕ␳
                myTransform->SetPosition({ myTransform->GetPosition().x, otherhitbox.max_.y + (myhitbox.max_.y - myhitbox.min_.y) / 2.0f, myTransform->GetPosition().z });
            }
        }
    }
}
