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
#include <map>
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

	void Init(void)override;
	void Uninit(void) override;
	void Update(void) override {};

	void AllUpdate(GameObject* _other, size_t _id);
	void AddEvent(std::function<void(GameObject* _other)>& _event);	// �Ƃ肠�����I�u�W�F�N�g���Ɠn��
	void RemoveEvent();	// ����Ȃ��Ȃ����I�u�W�F�N�g�������\��

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	std::map<size_t, std::function<void(GameObject*)>> functions_{};
};
#endif // COLLIDER_EVENT_COMPONENT_H_

