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
// @brief �Փ˂��������鏈��
// @param _other �Փ˂����I�u�W�F�N�g
//-----------------------------------------------------------------
void PushOutComponent::ResolveCollision(GameObject* other) {
    auto myTransform = owner_->GetComponent<TransformComponent>();
    auto myCollider = owner_->GetComponent<BoxColliderComponent>();
    auto otherTransform = other->GetComponent<TransformComponent>();
    auto otherCollider = other->GetComponent<BoxColliderComponent>();

    // �K�v�ȃR���|�[�l���g���Ȃ���Ή������Ȃ�
    if (!myTransform || !myCollider || !otherTransform || !otherCollider)
    {
        return;
    }

    // �����Ƒ���� AABB ���擾
    auto myBox = myCollider->GetBoxSize();
    auto myPos = myTransform->GetPosition();
    auto otherBox = otherCollider->GetBoxSize();
    auto otherPos = otherTransform->GetPosition();

    // �y�l�g���[�V�����ʂ��v�Z
    DirectX::SimpleMath::Vector3 penetration = CalculatePushOut(myPos, myBox, otherPos, otherBox);

    // �����̈ʒu�������o��
    myTransform->SetPosition(myPos + penetration);
}


//-----------------------------------------------------------------
// @brief �����o���ʂ��v�Z����
// @param myPos �����̈ʒu, myBox ������AABB, otherPos ����̈ʒu, otherBox �����AABB
// @return �����o����
//-----------------------------------------------------------------
DirectX::SimpleMath::Vector3 PushOutComponent::CalculatePushOut(
    const DirectX::SimpleMath::Vector3& myPos, const DirectX::SimpleMath::Vector4& myBox,
    const DirectX::SimpleMath::Vector3& otherPos, const DirectX::SimpleMath::Vector4& otherBox
) {
    // ������AABB���E���v�Z
    DirectX::SimpleMath::Vector3 myMin = { myBox.y, myBox.x , 0.0f };    // ����
	DirectX::SimpleMath::Vector3 myMax = { myBox.z, myBox.w , 0.0f };	// �E��

    // �����AABB���E���v�Z
    DirectX::SimpleMath::Vector3 otherMin = { otherBox.y, otherBox.x , 0.0f  };
    DirectX::SimpleMath::Vector3 otherMax = { otherBox.z, otherBox.w , 0.0f  };

    // �d�Ȃ�ʂ��v�Z
    float overlapX = min(myMax.x, otherMax.x) - max(myMin.x, otherMin.x);
    float overlapY = min(myMax.y, otherMax.y) - max(myMin.y, otherMin.y);

    // �ŏ��̏d�Ȃ�ʂ������o�������Ƃ��ĕԂ�
    if (overlapX < overlapY) {return { overlapX * (myPos.x < otherPos.x ? -1.0f : 1.0f), 0.0f, 0.0f };
    }
    else {
        return { 0.0f, overlapY * (myPos.y < otherPos.y ? -1.0f : 1.0f), 0.0f };
    }
}
