//=================================================================
// [GameManager.h] ゲームマネージャーモジュールヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態やオブジェクトを管理するためのクラス
//=================================================================
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

/*----- インクルード -----*/
#include "StdAfx.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//-----------------------------------------------------------------
// ゲームマネージャークラス
//-----------------------------------------------------------------
class GameManager
{
public:
	enum class GameState
	{
		None = -1
		, Title
		, Gameplay
		, Result
		, Paused
		, Quit

		, MAX
	};

public:
	GameManager(HWND* hWnd);
	~GameManager(void);

	class GameManager* Create(HWND* _hWnd)
	{
		return new GameManager(_hWnd);
	}

	void InitAll(void);
	void UninitAll(void);
	void InputAll(void);
	void UpdateAll(float deltaTime);
	void GenerateOutputAll(void);

	class Direct3D* GetRenderer(void) { return direct3D_; }

public: 
	// ゲームオブジェクトの追加と削除
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);


private:
	// 各更新処理
	void UpdateGameObjects(float deltaTime);

private:
	// 現在のゲームの状態
	GameState game_state_;

	// 各オブジェクトが更新中か確認
	bool updating_game_objects_;
	
	// ウィンドウの情報
	HWND* hWnd_;

	// ゲームオブジェクト
	std::vector<class GameObject*> game_objects_;
	std::vector<class GameObject*> pending_game_objects_;

private:
	// ここに作ったオブジェクトを置いていく(?)

	class Direct3D* direct3D_;
};


#endif GAME_MANAGER_H_
//=================================================================
//			End of File 
//=================================================================

