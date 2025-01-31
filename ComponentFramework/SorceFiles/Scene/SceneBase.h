//==================================================
// [SceneBase.h] �V�[���x�[�X�N���X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�V�[���̊��N���X
//==================================================
#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include <vector>
#include <array>
#include "../GameObjects/GameObject.h"

/*----- �O���錾 -----*/
class TileMapManager;
class GameManager;

// �V�[����	
enum SceneName {
	Title,

	Tutorial,
	Stage1_1,
	Stage1_2,
	Stage1_3,
	Stage1_4,

	Stage2_1,
	Stage2_2,
	Stage2_3,
	Stage2_4,

	Stage3_1,
	Stage3_2,
	Stage3_3,
	Stage3_4,

	Result,
};
//--------------------------------------------------
// �V�[���x�[�X�N���X
//--------------------------------------------------
class SceneBase
{
public:
	enum StageState
	{
		None = -1,
		Game,
		Pouse,
		Result,
		Rewind,
		Max
	};
	SceneBase(GameManager* _gameManager, std::string _sceneName);
	virtual ~SceneBase();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;	// �V�[���؂�ւ��̏����Ƃ���Scene��Update�ɏ����������Ƃ������܂�

	void HammerCountDown() { hammerMaxCount_--; }
	int GetGearMaxCount() { return gearMaxCount_; }
	bool GetIsHammerMax() { return isHammerMax_; }

	std::string GetSceneName() const { return scene_name_; }	
	void SetNextSceneName(SceneName _nextScene) { next_scene_name_ = _nextScene; }	// ���̃V�[���֑J�ڂ���֐�
	void SetOldSceneName(std::string _oldSceneName) { old_scene_name_ = _oldSceneName; }	// �O�̃V�[������ݒ�
protected:
	StageState stageState_ = StageState::None;

	void PauseWindow();	// �|�[�Y��ʂ̕\���E����֐�
	void OptionWindow();
	void NumberChange();	// ������ω�������

	GameManager* game_manager_{};
	std::unique_ptr<TileMapManager> tile_map_manager_;

	std::string scene_name_{};
	std::string old_scene_name_{};	// �O�̃V�[������ۑ�
	SceneName next_scene_name_;		// ���̃V�[������ۑ�

	// �X�e�[�WUI�֘A
	int gearMaxCount_ = 0;	// �ő�M�A�l�����̒萔����
	int hammerMaxCount_ = 0;
	bool isHammerMax_ = false;
	std::array<class Revolution*, 2> stageUIs_{};	// �����Ȃ��X�e�[�WUI
	Revolution* gearMax_{};							// �X�e�[�W���Ƃ̃M�A�̍ő吔
	Revolution* gearGet_{};							// �X�e�[�W���ƂɃQ�b�g�����M�A�̐�
	Revolution* hammerNum_{};						// �X�e�[�W���Ƃɐݒ肳�ꂽ�@�����
	// �|�[�Y��ʊ֘A
	bool isWindowOpen = false;						// ���������I�v�V�����̍Œ��Ƀ{�^��������s��Ȃ��悤�ɂ���
	int pause_select_button_ = 0;					// �|�[�Y��ʂ̃{�^���̓Y����
	Revolution* pauseWindow_{};						// �|�[�Y��ʂ̃E�B���h�E
	Revolution* pause_instruction_{};				// ��������摜
	std::array<Revolution*, 5>	 pauseButtons_{};	// �|�[�Y��ʂ̃{�^��
};
#endif  // SCENE_BASE_H_