//==================================================
// [CallBackComponent.h] �R�[���o�b�N�����삷�邩�e�X�g����R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F�R�[���o�b�N�e�X�g�p�R���|�[�l���g
//==================================================
#ifndef CALLBACK_COMPONENT_H_
#define CALLBACK_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �\���̐錾 -----*/
/*----- �O���錾 -----*/
//--------------------------------------------------
// �R�[���o�b�N�e�X�g�p�N���X
//--------------------------------------------------
class CallBackComponent :public Component
{
public:
	CallBackComponent(GameObject* _owner, int _updateOrder = 50);
	~CallBackComponent();
	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
private:
};
#endif // CALLBACK_COMPONENT_H_