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
#include "Scene/Stage1_1Scene.h"
#include "Scene/Stage1_2Scene.h"
#include "Scene/Stage1_3Scene.h"
#include "Scene/Stage1_4Scene.h"
#include "Scene/Stage1_5Scene.h"
/*----- 構造体定義 -----*/
// シーン名	
enum SceneName {
	Title,
	Stage1_1,
	Stage1_2,
	Stage1_3,
	Stage1_4,
	Stage1_5,
	Result,
};


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

	// シーン切り替え
	void ChangeScene(SceneName _scene);

	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* _gameObject);
	// ゲームオブジェクトの削除
	void RemoveGameObject(GameObject* _gameObject);
private:
	int itemCount = 0;
	// 更新処理
	void UpdateGameObjects(void);
	// シーン
	SceneBase* current_scene_{};

	// オブジェクトが更新中か確認
	bool updating_game_objects_;

	class Renderer* renderer_{};	// レンダラー
	class AudioManager* audio_manager_{};	// オーディオマネージャー
	class ColliderManager* collider_manager_{};				// コライダーマネージャー
	class PendulumManager* pendulum_manager_{};				// 振り子マネージャー

	// ゲームオブジェクト
	std::vector<GameObject*> game_objects_{};			// ゲームオブジェクトコンテナ
	std::vector<GameObject*> pending_game_objects_{};	// 待機コンテナ
};


#endif //GAME_MANAGER_H_