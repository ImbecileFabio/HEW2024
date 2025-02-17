//==================================================
// [SceneBase.h] シーンベースクラス
// 著者：有馬啓太
//--------------------------------------------------
// 説明：シーンの基底クラス
//==================================================
#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

/*----- インクルード -----*/
#include <memory>
#include <vector>
#include <array>
#include "../GameObjects/GameObject.h"

/*----- 前方宣言 -----*/
class TileMapManager;
class GameManager;

// シーン名	
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
// シーンベースクラス
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
	virtual void Update() = 0;	// シーン切り替えの条件とかをSceneのUpdateに書く感じだとおもいます

	void HammerCountDown() { hammerMaxCount_--; }
	int GetGearMaxCount() { return gearMaxCount_; }
	bool GetIsHammerMax() { return isHammerMax_; }

	std::string GetSceneName() const { return scene_name_; }	
	void SetNextSceneName(SceneName _nextScene) { next_scene_name_ = _nextScene; }	// 次のシーンへ遷移する関数
	void SetOldSceneName(std::string _oldSceneName) { old_scene_name_ = _oldSceneName; }	// 前のシーン名を設定
protected:
	StageState stageState_ = StageState::None;

	void PauseWindow();	// ポーズ画面の表示・操作関数
	void OptionWindow();
	void NumberChange();	// 数字を変化させる

	GameManager* game_manager_{};
	std::unique_ptr<TileMapManager> tile_map_manager_;

	std::string scene_name_{};
	std::string old_scene_name_{};	// 前のシーン名を保存
	SceneName next_scene_name_;		// 次のシーン名を保存

	// ステージUI関連
	int gearMaxCount_ = 0;	// 最大ギア獲得数の定数を代入
	int hammerMaxCount_ = 0;
	bool isHammerMax_ = false;
	std::array<class Revolution*, 2> stageUIs_{};	// 動かないステージUI
	Revolution* gearMax_{};							// ステージごとのギアの最大数
	Revolution* gearGet_{};							// ステージごとにゲットしたギアの数
	Revolution* hammerNum_{};						// ステージごとに設定された叩ける回数
	// ポーズ画面関連
	bool isWindowOpen = false;						// 操作説明やオプションの最中にボタン操作を行わないようにする
	int pause_select_button_ = 0;					// ポーズ画面のボタンの添え字
	Revolution* pauseWindow_{};						// ポーズ画面のウィンドウ
	Revolution* pause_instruction_{};				// 操作説明画像
	std::array<Revolution*, 4>	 pauseButtons_{};	// ポーズ画面のボタン

	std::unique_ptr<class AudioManager> audio_manager_;
};
#endif  // SCENE_BASE_H_