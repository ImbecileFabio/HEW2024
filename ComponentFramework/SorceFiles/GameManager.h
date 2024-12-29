//=================================================================
// [GameManager.h] �Q�[���}�l�[�W���[���W���[���w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Q�[���̏�Ԃ�Scene�A�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- �C���N���[�h -----*/
#include<memory>
#include<vector>

#include "Scene/TitleScene.h"
#include "Scene/ResultScene.h"
#include "Scene/Stage1_1Scene.h"
#include "Scene/Stage1_2Scene.h"
#include "Scene/Stage1_3Scene.h"
#include "Scene/Stage1_4Scene.h"
#include "Scene/Stage1_5Scene.h"
/*----- �\���̒�` -----*/
// �V�[����	
enum SceneName {
	Title,
	Stage1_1,
	Stage1_2,
	Stage1_3,
	Stage1_4,
	Stage1_5,
	Result,
};


/*----- �O���錾 -----*/
class SceneBase;
class GameObject;
class ColliderManager;
class PendulumManager;

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
	auto& GetAudioManager(void) const { return audio_manager_; }
	auto& GetColliderManager() const { return collider_manager_; }
	auto& GetPendulumManager() const { return pendulum_manager_; }
	
	auto& GetGameObjects() const { return game_objects_; }
	auto& GetPendingGameObjects() const { return pending_game_objects_; }
	
	void itemCountUp() { itemCount++; }
	int GetItemCount() { return itemCount; }

	// �V�[���؂�ւ�
	void ChangeScene(SceneName _scene);

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
	void RemoveGameObject(GameObject* _gameObject);
private:
	int itemCount = 0;
	// �X�V����
	void UpdateGameObjects(void);
	// �V�[��
	SceneBase* current_scene_{};

	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;

	class Renderer* renderer_{};	// �����_���[
	class AudioManager* audio_manager_{};	// �I�[�f�B�I�}�l�[�W���[
	class ColliderManager* collider_manager_{};				// �R���C�_�[�}�l�[�W���[
	class PendulumManager* pendulum_manager_{};				// �U��q�}�l�[�W���[

	// �Q�[���I�u�W�F�N�g
	std::vector<GameObject*> game_objects_{};			// �Q�[���I�u�W�F�N�g�R���e�i
	std::vector<GameObject*> pending_game_objects_{};	// �ҋ@�R���e�i
};


#endif //GAME_MANAGER_H_