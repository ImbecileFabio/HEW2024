//==================================================
// [ColliderEventComponent.h] �C�x���g�������s���R���|�[�l���g�̃x�[�X�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�C�x���g�������s���R���|�[�l���g�̃x�[�X�N���X
//==================================================
#ifndef COLLIDER_EVENT_COMPONENT_H_
#define COLLIDER_EVENT_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "EventBaseComponent.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �R���C�_�[�̃C�x���g�������s���N���X
//--------------------------------------------------
class ColliderEventComponent :
    public EventBaseComponent
{
public:
	ColliderEventComponent(GameObject* _owner, int _updateOrder = 50) :EventBaseComponent(_owner, _updateOrder) {};
	~ColliderEventComponent() {};

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
};

#endif // COLLIDER_EVENT_COMPONENT_H_

