//==================================================
// [EventBaseComponent.h] �C�x���g�������s���R���|�[�l���g�̃x�[�X�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�C�x���g�������s���R���|�[�l���g�̃x�[�X�N���X
//==================================================
#ifndef EVENT_BASE_COMPONENT_H_
#define EVENT_BASE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include "../../Component.h"
/*----- �\���̒�` -----*/
/*----- �O���錾 -----*/
//--------------------------------------------------
// �C�x���g�������s���x�[�X�N���X�@���̂ɂ��Ďg��Ȃ��恙�c
//--------------------------------------------------
class EventBaseComponent : public Component
{
public:
	EventBaseComponent(GameObject* _owner, int _updateOrder = 50) :Component(_owner, _updateOrder) {};
	~EventBaseComponent() {};

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }	// TODO���Ƃŕς���
};
#endif // EVENT_BASE_COMPONENT_H_