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
	void Update(void) override {};
	// �C�x���g�@�\�̊�{�I�ȏ���
	virtual void AddEvent(std::function<void> _event) = 0;

	TypeID GetComponentType(void) const override { return TypeID::EventBaseComponent; }
protected:
};
#endif // EVENT_BASE_COMPONENT_H_