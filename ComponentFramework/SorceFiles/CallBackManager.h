//=================================================================
// [CallBackManager.h] �R�[���o�b�N�}�l�[�W���[���W���[���w�b�_
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�R�[���o�b�N�ŌĂт����C�x���g���̊Ǘ����s���N���X
//=================================================================
#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_
/*----- �C���N���[�h -----*/
#include<memory>
#include<vector>
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//-----------------------------------------------------------------
// �R�[���o�b�N�[�}�l�[�W���[�N���X
//-----------------------------------------------------------------
class CallBackManager
{
public:
	CallBackManager(void);
	~CallBackManager(void);
	// �C���X�^���X����
	static auto Create(void) { return new CallBackManager(); }

private:
};
#endif // CALLBACK_MANAGER_H_