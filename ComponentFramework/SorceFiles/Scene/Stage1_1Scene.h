//==================================================
// [Stage1_1Scene.h] ステージ1-1シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-1を管理をするクラス
//==================================================
#ifndef STAGE1_1SCENE_H_
#define STAGE1_1SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"

//--------------------------------------------------
// ステージ1-1シーンクラス
//--------------------------------------------------
class Stage1_1Scene :
	public SceneBase
{
public:
	Stage1_1Scene(GameManager* _gameManager);
	~Stage1_1Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// ゲームの状態
	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
	STATE State;

	// 作ったオブジェクトをここに記述
	class BackGround* back_ground_{};	// 背景
	class Camera* camera_{};			// カメラ
	class Pendulum* pendulum_{};		// 振り子
	class Pendulum* pendulum_2_{};
	class Pendulum* pendulum_3_{};
	class Tile* tile_{};				// タイル
	class Robot* robot_{};				// ロボット
	class Lift*	 lift_{};				// リフト
	std::vector<class Item*> items_;	// アイテムリスト
};
#endif  // STAGE1_1SCENE_H_