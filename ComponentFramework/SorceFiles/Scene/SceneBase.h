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

	std::string GetSceneName() const { return scene_name_; }								// 現在のシーン名を取得
	void SetOldSceneName(std::string _oldSceneName) { old_scene_name_ = _oldSceneName; }	// 前のシーン名を設定
protected:
	StageState stageState_ = StageState::None;

	void PauseWindow();	// ポーズ画面の表示・操作関数
	void OptionWindow();

	GameManager* game_manager_{};
	std::unique_ptr<TileMapManager> tile_map_manager_;

	std::string scene_name_{};
	std::string old_scene_name_{};	// 前のシーン名を保存

	// ステージUI関連
	std::array<class Revolution*, 2> stageUIs_{};	// 動かないステージUI
	// ポーズ画面関連
	bool isWindowOpen = false;						// 操作説明やオプションの最中にボタン操作を行わないようにする
	int pause_select_button_ = 0;					// ポーズ画面のボタンの添え字
	Revolution* pauseWindow_{};						// ポーズ画面のウィンドウ
	Revolution* pause_instruction_{};				// 操作説明画像
	std::array<Revolution*, 5>	 pauseButtons_{};	// ポーズ画面のボタン
	// ここに変化する画像を置く？
};
#endif  // SCENE_BASE_H_