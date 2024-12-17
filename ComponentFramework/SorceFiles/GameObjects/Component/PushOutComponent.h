//=================================================================
// [PushOutComponent.h] �����o���R���|�[�l���g
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�R���C�_�[�������Ă���ғ��m�������o���������s��
//=================================================================

#ifndef PUSH_OUT_COMPONENT_H_
#define PUSH_OUT_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <DirectXMath.h>
#include <SimpleMath.h>
#include "ColliderComponent/BoxColliderComponent.h"
#include "TransformComponent.h"

//-----------------------------------------------------------------
// �����o���R���|�[�l���g
//-----------------------------------------------------------------
class PushOutComponent : public Component {
public:
    PushOutComponent(GameObject* _owner, int _updateOrder = 50);
    ~PushOutComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override {};

	void ResolveCollision(GameObject* _other);


	TypeID GetComponentType(void) const override { return TypeID::PushOutComponent; }

private:
    DirectX::SimpleMath::Vector3 CalculatePushOut(
        const DirectX::SimpleMath::Vector3& myPos, const DirectX::SimpleMath::Vector4& myBox,
        const DirectX::SimpleMath::Vector3& otherPos, const DirectX::SimpleMath::Vector4& otherBox
    );

    // �p�ɂɌĂяo���悤�Ȃ�ŏ�������owner��Component���������o�ϐ��Ŏ����Ƃ����ق��������͌y�������H
};


#endif // PUSH_OUT_COMPONENT_H_