//=================================================================
// [GameManager.h] ゲームマネージャーモジュールヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態やオブジェクトを管理するためのクラス
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- インクルード -----*/
#include<memory>
#include<vector>

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
class Renderer;
class Player;
class Camera;
class Pendulum;

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

	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* _gameObject);
	// ゲームオブジェクトの削除
	void RemoveGameObject(GameObject* _gameObject);
	
private:
	//更新処理
	void UpdateGameObjects(void);

	// オブジェクトが更新中か確認
	bool updating_game_objects_;

	// ゲームオブジェクト
	std::vector<GameObject*> game_objects_{};			// ゲームオブジェクトコンテナ
	std::vector<GameObject*> pending_game_objects_{};	// 待機コンテナ

private:
	// 作ったオブジェクトをここに記述
	Renderer* renderer_{};	// レンダラー
	Player* player_{};		// プレイヤー
	Camera* camera_{};		// カメラ
	Pendulum* pendulum_{};	// 振り子
};


#endif //GAME_MANAGER_H_

