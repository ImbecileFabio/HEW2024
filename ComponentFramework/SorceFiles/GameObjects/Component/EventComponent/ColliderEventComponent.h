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
	ColliderEventComponent(GameObject* _owner, int _updateOrder = 50);
	~ColliderEventComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void AllTriggers();	// UPDATE�ŉ񂵂�BOOL��{TRUE����EFALSE}�ɂȂ�����
	void AllActions();
	void AddEvent	(std::function<void()> _event);
	void RemoveEvent(std::function<void()> _event) {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	std::list<std::function<void>> functions_{};	// �e�I�u�W�F�N�g�����R���C�_�[�ɔ������Ď��s����̂��֐�
};

#endif // COLLIDER_EVENT_COMPONENT_H_

