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
#include "Scene/TutorialScene.h"
#include "Scene/Stage1/Stage1_1Scene.h"
#include "Scene/Stage1/Stage1_2Scene.h"
#include "Scene/Stage1/Stage1_3Scene.h"
#include "Scene/Stage1/Stage1_4Scene.h"

#include "Scene/Stage2/Stage2_1Scene.h"
#include "Scene/Stage2/Stage2_2Scene.h"
#include "Scene/Stage2/Stage2_3Scene.h"
#include "Scene/Stage2/Stage2_4Scene.h"

#include "Scene/Stage3/Stage3_1Scene.h"
#include "Scene/Stage3/Stage3_2Scene.h"
#include "Scene/Stage3/Stage3_3Scene.h"
#include "Scene/Stage3/Stage3_4Scene.h"

/*----- �\���̒�` -----*/


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
	void UpdateAll(float _deltaTime);
	void GenerateOutputAll(void);

	auto& GetRenderer(void) const { return renderer_; }
	auto& GetColliderManager() const { return collider_manager_; }
	auto& GetPendulumManager() const { return pendulum_manager_; }
	auto& GetFadeManager() const { return fade_manager_; }
	
	auto& GetGameObjects() const { return game_objects_; }
	auto& GetPendingGameObjects() const { return pending_game_objects_; }
	
	// �Q�[���̏I���t���O
	void SetEndFlag(bool _endFg) { endFg = _endFg; }
	bool GetEndFlag() { return endFg; }
	void itemCountUp() { itemCount++; }
	void ResetItemCount() { itemCount = 0; }
	int GetItemCount() { return itemCount; }
	void HammerCountDown() {current_scene_->HammerCountDown(); }
	bool GetIsHammerMax() { return current_scene_->GetIsHammerMax(); }
	// �I�u�W�F�N�g�����ׂăN���A
	void ClearAllObjects(void);

	void TransitionToScene(SceneName _nextScene);
	// �V�[���؂�ւ�
	void ChangeScene(SceneName _nextScene);

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
	void RemoveGameObject(GameObject* _gameObject);
private:
	// �Q�[���̏I���t���O
	bool endFg = false;

	int itemCount = 0;
	// �X�V����
	void UpdateGameObjects(float _deltaTime);
	// �V�[��
	SceneBase* current_scene_{};
	bool is_transitioning_scene_{};	// �V�[���؂�ւ���Ԃ�

	bool tutorial_completed_;	// �`���[�g���A���N���A�t���O

	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;

	class Renderer* renderer_{};	// �����_���[
	class FadeManager* fade_manager_{};	// �t�F�[�h�}�l�[�W��

	class ColliderManager* collider_manager_{};				// �R���C�_�[�}�l�[�W���[
	class PendulumManager* pendulum_manager_{};				// �U��q�}�l�[�W���[

	// �Q�[���I�u�W�F�N�g
	std::vector<GameObject*> game_objects_{};			// �Q�[���I�u�W�F�N�g�R���e�i
	std::vector<GameObject*> pending_game_objects_{};	// �ҋ@�R���e�i

};


#endif //GAME_MANAGER_H_