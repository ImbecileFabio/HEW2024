//=================================================================
// [GameManager.h] ゲームマネージャーモジュールヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態やオブジェクトを管理するためのクラス
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


/*----- インクルード -----*/

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
class Renderer;
class Player;
class Camera;

//-----------------------------------------------------------------
// ゲームマネージャークラス
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

	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
	
private:
	void UpdateGameObjects(void);	//更新処理

	// オブジェクトが更新中か確認
	bool updating_game_objects_;

	// ゲームオブジェクト
	std::vector<GameObject*> game_objects_{};			// ゲームオブジェクトコンテナ
	std::vector<GameObject*> pending_game_objects_{};	// 待機コンテナ

private:
	// 作ったオブジェクトをここに記述
	std::shared_ptr<Renderer> renderer_{};	// レンダラー
	std::shared_ptr<Player> player_{};		// プレイヤー
	std::shared_ptr<Camera> camera_{};		// カメラ
};


#endif //GAME_MANAGER_H_

