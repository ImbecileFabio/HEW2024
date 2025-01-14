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

	std::string GetSceneName() const { return scene_name_; }								// ���݂̃V�[�������擾
	void SetOldSceneName(std::string _oldSceneName) { old_scene_name_ = _oldSceneName; }	// �O�̃V�[������ݒ�
protected:
	StageState stageState_ = StageState::None;

	void PauseWindow();	// �|�[�Y��ʂ̕\���E����֐�
	void OptionWindow();

	GameManager* game_manager_{};
	std::unique_ptr<TileMapManager> tile_map_manager_;

	std::string scene_name_{};
	std::string old_scene_name_{};	// �O�̃V�[������ۑ�

	// �X�e�[�WUI�֘A
	std::array<class Revolution*, 2> stageUIs_{};	// �����Ȃ��X�e�[�WUI
	// �|�[�Y��ʊ֘A
	bool isWindowOpen = false;						// ���������I�v�V�����̍Œ��Ƀ{�^��������s��Ȃ��悤�ɂ���
	int pause_select_button_ = 0;					// �|�[�Y��ʂ̃{�^���̓Y����
	Revolution* pauseWindow_{};						// �|�[�Y��ʂ̃E�B���h�E
	Revolution* pause_instruction_{};				// ��������摜
	std::array<Revolution*, 5>	 pauseButtons_{};	// �|�[�Y��ʂ̃{�^��
	// �����ɕω�����摜��u���H
};
#endif  // SCENE_BASE_H_