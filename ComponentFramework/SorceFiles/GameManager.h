//=================================================================
// [GameManager.h] �Q�[���}�l�[�W���[���W���[���w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Q�[���̏�Ԃ�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- �C���N���[�h -----*/

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
class Renderer;
class Player;
class Camera;

//-----------------------------------------------------------------
// �Q�[���}�l�[�W���[�N���X
//-----------------------------------------------------------------
class GameManager
{
public:
	GameManager(void);
	~GameManager(void);
	
	static std::shared_ptr<GameManager> Create(void)
	{
		return std::make_shared<GameManager>();
	}

	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	void GenerateOutputAll(void);

	auto GetRenderer(void) const { return renderer_; }

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
	
private:
	void UpdateGameObjects(void);	//�X�V����

	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;

	// �Q�[���I�u�W�F�N�g
	std::vector<GameObject*> game_objects_{};			// �Q�[���I�u�W�F�N�g�R���e�i
	std::vector<GameObject*> pending_game_objects_{};	// �ҋ@�R���e�i

private:
	// ������I�u�W�F�N�g�������ɋL�q
	std::shared_ptr<Renderer> renderer_{};	// �����_���[
	std::shared_ptr<Player> player_{};		// �v���C���[
	std::shared_ptr<Camera> camera_{};		// �J����
};


#endif //GAME_MANAGER_H_

