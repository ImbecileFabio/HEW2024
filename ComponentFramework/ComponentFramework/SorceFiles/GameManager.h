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
	GameManager(void);
	~GameManager(void);
	
	class GameManager* Create(void)
	{
		return new GameManager();
	}

	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	void GenerateOutputAll(void);

	class Renderer* GetRenderer(void) { return renderer_; }

	// ゲームオブジェクトの追加
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);

private:
	void UpdateGameObjects(void);	//更新処理

	// オブジェクトが更新中か確認
	bool updating_game_objects_;

	// ゲームオブジェクト
	std::vector<class GameObject*> game_objects_;
	std::vector<class GameObject*> pending_game_objects_;

private:
	// 作ったオブジェクトをここに記述
	class Renderer* renderer_;	// レンダラー
};


#endif GAME_MANAGER_H_
//=================================================================
//			End of File 
//=================================================================

