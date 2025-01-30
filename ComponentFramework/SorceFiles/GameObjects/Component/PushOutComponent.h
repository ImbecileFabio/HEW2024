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
    PushOutComponent(GameObject* _owner, int _updateOrder = 15);
    ~PushOutComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override {};

	void ResolveCollision(GameObject* _other);


	TypeID GetComponentType(void) const override { return TypeID::PushOutComponent; }

private:

};


#endif // PUSH_OUT_COMPONENT_H_