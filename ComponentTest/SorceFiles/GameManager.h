//=================================================================
// [GameManager.h] �Q�[���}�l�[�W���[���W���[���w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Q�[���̏�Ԃ�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

/*----- �C���N���[�h -----*/
#include "StdAfx.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//-----------------------------------------------------------------
// �Q�[���}�l�[�W���[�N���X
//-----------------------------------------------------------------
class GameManager
{
public:
	enum class GameState
	{
		None = -1
		, Title
		, Gameplay
		, Result
		, Paused
		, Quit

		, MAX
	};

public:
	GameManager(HWND* hWnd);
	~GameManager(void);

	class GameManager* Create(HWND* _hWnd)
	{
		return new GameManager(_hWnd);
	}

	void InitAll(void);
	void UninitAll(void);
	void InputAll(void);
	void UpdateAll(float deltaTime);
	void GenerateOutputAll(void);

	class Direct3D* GetRenderer(void) { return direct3D_; }

public: 
	// �Q�[���I�u�W�F�N�g�̒ǉ��ƍ폜
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);


private:
	// �e�X�V����
	void UpdateGameObjects(float deltaTime);

private:
	// ���݂̃Q�[���̏��
	GameState game_state_;

	// �e�I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;
	
	// �E�B���h�E�̏��
	HWND* hWnd_;

	// �Q�[���I�u�W�F�N�g
	std::vector<class GameObject*> game_objects_;
	std::vector<class GameObject*> pending_game_objects_;

private:
	// �����ɍ�����I�u�W�F�N�g��u���Ă���(?)

	class Direct3D* direct3D_;
};


#endif GAME_MANAGER_H_
//=================================================================
//			End of File 
//=================================================================

