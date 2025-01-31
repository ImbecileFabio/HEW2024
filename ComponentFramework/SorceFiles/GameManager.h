//=================================================================
// [GameManager.h] ゲームマネージャーモジュールヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態やScene、オブジェクトを管理するためのクラス
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- インクルード -----*/
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

/*----- 構造体定義 -----*/


/*----- 前方宣言 -----*/
class SceneBase;
class GameObject;
class ColliderManager;
class PendulumManager;

//-----------------------------------------------------------------
// ゲームマネージャークラス
//-----------------------------------------------------------------
class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	// インスタンス生成
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
	
	// ゲームの終了フラグ
	void SetEndFlag(bool _endFg) { endFg = _endFg; }
	bool GetEndFlag() { return endFg; }
	void itemCountUp() { itemCount++; }
	void ResetItemCount() { itemCount = 0; }
	int GetItemCount() { return itemCount; }
	void HammerCountDown() {current_scene_->HammerCountDown(); }
	bool GetIsHammerMax() { return current_scene_->GetIsHammerMax(); }
	// オブジェクトをすべてクリア
	void ClearAllObjects(void);

	void TransitionToScene(SceneName _nextScene);
	// シーン切り替え
	void ChangeScene(SceneName _nextScene);

	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* _gameObject);
	// ゲームオブジェクトの削除
	void RemoveGameObject(GameObject* _gameObject);
private:
	// ゲームの終了フラグ
	bool endFg = false;

	int itemCount = 0;
	// 更新処理
	void UpdateGameObjects(float _deltaTime);
	// シーン
	SceneBase* current_scene_{};
	bool is_transitioning_scene_{};	// シーン切り替え状態か

	bool tutorial_completed_;	// チュートリアルクリアフラグ

	// オブジェクトが更新中か確認
	bool updating_game_objects_;

	class Renderer* renderer_{};	// レンダラー
	class FadeManager* fade_manager_{};	// フェードマネージャ

	class ColliderManager* collider_manager_{};				// コライダーマネージャー
	class PendulumManager* pendulum_manager_{};				// 振り子マネージャー

	// ゲームオブジェクト
	std::vector<GameObject*> game_objects_{};			// ゲームオブジェクトコンテナ
	std::vector<GameObject*> pending_game_objects_{};	// 待機コンテナ

};


#endif //GAME_MANAGER_H_