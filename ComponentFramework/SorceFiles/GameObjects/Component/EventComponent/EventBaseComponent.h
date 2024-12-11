////==================================================
//// [EventBaseComponent.h] �C�x���g�������s���R���|�[�l���g�̃x�[�X�w�b�_
//// ���ҁF����仓�
////--------------------------------------------------
//// �����F�C�x���g�������s���R���|�[�l���g�̃x�[�X�N���X
////==================================================
//#ifndef EVENT_BASE_COMPONENT_H_
//#define EVENT_BASE_COMPONENT_H_
///*----- �C���N���[�h -----*/
//#include <memory>
//#include <unordered_map>
//#include <functional>
//#include <string>
//#include "../../Component.h"
///*----- �\���̒�` -----*/
///*----- �O���錾 -----*/
////--------------------------------------------------
//// �C�x���g�������s���x�[�X�N���X�@���̂ɂ��Ďg��Ȃ�
////--------------------------------------------------
//class EventBaseComponent : public Component
//{
//public:
//	EventBaseComponent(GameObject* _owner, int _updateOrder = 50) :Component(_owner, _updateOrder) {};
//	~EventBaseComponent() = default;
//
//	void Init(void) override {};
//	void Uninit(void) override {};
//	void Update(void) override {};
//	// �C�x���g�@�\�̊�{�I�ȏ���
//	void AddEventListener(std::string _eventName, std::function<void>);	// �C�x���g���X�i�[��o�^
//	void EmitEvent();			// �C�x���g�𔭍s
//
//	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }	// TODO���Ƃŕς���
//protected:
//	// �C�x���g�̖��O�ƃC�x���g���X�g��΂ɂ���
//	std::unordered_map<std::string, std::list<std::function<void>>> listeners_; // �C�x���g���Ƃ̃��X�i�[���X�g
//	std::list<std::function<Component>> functions_;	// �C�x���g���i�[���郊�X�g
//};
//#endif // EVENT_BASE_COMPONENT_H_