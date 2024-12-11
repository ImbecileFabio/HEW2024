//==================================================
// [EventDebugComponent.h] �C�x���g�����m�F�N���X�̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F�R���C�_�C�x���g�����������������Ă��邩�ǂ������e�X�g����N���X
//==================================================
#ifndef EVENT_DEBUG_COMPONENT_H_
#define EVENT_DEBUG_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
//--------------------------------------------------
// �C�x���g�f�o�b�N�p�R���|�[�l���g
//--------------------------------------------------
class EventDebugComponent : public Component
{
public:
	EventDebugComponent(GameObject* _owner, int updateOrder = 50);
	~EventDebugComponent();

	void Init() override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::EventDebugComponent; }
private:
};

#endif // EVENT_DEBUG_COMPONENT_H_

