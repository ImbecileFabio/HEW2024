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
#include <unordered_map>
#include <functional>
#include <string>
#include "../../Component.h"
#include "../../GameObject.h"
/*----- �\���̒�` -----*/
/*----- �O���錾 -----*/
//--------------------------------------------------
// �C�x���g�������s���x�[�X�N���X�@���̂ɂ��Ďg��Ȃ�
//--------------------------------------------------
class EventBaseComponent : public Component
{
public:
	EventBaseComponent(GameObject* _owner, int _updateOrder = 50) :Component(_owner, _updateOrder) {};
	~EventBaseComponent() = default;

	void Init(void) override {};
	void Uninit(void) override {};
	virtual void Update(void) override {};
	virtual void AllUpdate(GameObject* _other, size_t _id) {};	// TRUE�ɂȂ����֐������s
	// �C�x���g�R���|�[�l���g���Ƃ�AddEvent�̈����Ⴂ���I�[�o�[���[�h�Œu���Ƃ�
	virtual void AddEvent(std::function<void(GameObject* _other)>& _event) {};
	virtual void RemoveEvent() {};	// ����Ȃ��Ȃ����I�u�W�F�N�g�������\��
	size_t GetId() { return id_; }

	TypeID GetComponentType(void) const override { return TypeID::EventBaseComponent; }
protected:
	size_t id_{};
	static size_t generalId_;	// AddEvent�����Ƃ��ɉ��Z���āA���̒l���ʂ̃R���|�[�l���g��ID�ɓ����
};
#endif // EVENT_BASE_COMPONENT_H_