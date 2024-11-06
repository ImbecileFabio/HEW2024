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
class GameObject;
class Renderer;
class Player;

//-----------------------------------------------------------------
// �Q�[���}�l�[�W���[�N���X
//-----------------------------------------------------------------
class GameManager
{
public:
	GameManager(void);
	~GameManager(void);
	
	static GameManager* Create(void)
	{
		return new GameManager();
	}

	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	void GenerateOutputAll(void);

	Renderer* GetRenderer(void) { return renderer_; }

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
	
private:
	void UpdateGameObjects(void);	//�X�V����

	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;

	// �Q�[���I�u�W�F�N�g
	std::vector<GameObject*> game_objects_;
	std::vector<GameObject*> pending_game_objects_;

private:
	// ������I�u�W�F�N�g�������ɋL�q
	Renderer* renderer_;	// �����_���[
	Player* player_;		// �v���C���[
};


#endif //GAME_MANAGER_H_
//=================================================================
//			End of File 
//=================================================================

