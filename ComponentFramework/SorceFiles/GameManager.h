//=================================================================
// [GameManager.h] �Q�[���}�l�[�W���[���W���[���w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Q�[���̏�Ԃ�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- �C���N���[�h -----*/
#include<memory>
#include<vector>

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
class Renderer;
class Player;
class Camera;
class Pendulum;

//-----------------------------------------------------------------
// �Q�[���}�l�[�W���[�N���X
//-----------------------------------------------------------------
class GameManager
{
public:
	GameManager(void);
	~GameManager(void);
	
	// �C���X�^���X����
	static auto Create(void) { return new GameManager(); }

	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	void GenerateOutputAll(void);

	auto& GetRenderer(void) const { return renderer_; }

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
	void RemoveGameObject(GameObject* _gameObject);
	
private:
	//�X�V����
	void UpdateGameObjects(void);

	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;

	// �Q�[���I�u�W�F�N�g
	std::vector<GameObject*> game_objects_{};			// �Q�[���I�u�W�F�N�g�R���e�i
	std::vector<GameObject*> pending_game_objects_{};	// �ҋ@�R���e�i

private:
	// ������I�u�W�F�N�g�������ɋL�q
	Renderer* renderer_{};	// �����_���[
	Player* player_{};		// �v���C���[
	Camera* camera_{};		// �J����
	Pendulum* pendulum_{};	// �U��q
};


#endif //GAME_MANAGER_H_

