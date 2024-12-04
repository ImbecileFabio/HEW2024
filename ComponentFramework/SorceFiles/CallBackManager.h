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
#include<functional>
#include<unordered_map>
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//-----------------------------------------------------------------
// �R�[���o�b�N�[�}�l�[�W���[�N���X
//-----------------------------------------------------------------
class CallBackManager
{
public:
	CallBackManager (void) = default;
	~CallBackManager(void) = default;
	// �C���X�^���X����
	static auto Create(void) { return new CallBackManager(); }

	using Callback = std::function<void()>;	// �R�[���o�b�N�֐��^

private:
};
#endif // CALLBACK_MANAGER_H_