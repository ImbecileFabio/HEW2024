//==================================================
// [GameProcess.h] �Q�[�����s�������W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���̎��s�������܂Ƃ߂��N���X�炵��
//==================================================
#ifndef GAME_PROCESS_H_
#define GAME_PROCESS_H_

/*----- �C���N���[�h -----*/

/*----- �\���̒�` -----*/


/*----- �O���錾 -----*/


//--------------------------------------------------
// �Q�[���v���Z�X�N���X
//--------------------------------------------------
class GameProcess
{
public:
	GameProcess(HWND* hWnd);
	~GameProcess(void);

public:
	bool StartUp(void);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);
	void ProcessInput(void);
	void Update(float deltaTime);
	void GenerateOutput(void);

private:
	class GameManager* game_manager_;
	HWND* hWnd_;
};

#endif // GAME_PROCESS_H_
//==================================================
//				End of FIle
//==================================================
