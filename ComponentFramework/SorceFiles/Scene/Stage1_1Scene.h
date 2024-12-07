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

//==================================================
// ステージ1-1シーンクラス
//==================================================
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
	// 作ったオブジェクトをここに記述

	class Player* player_{};		// プレイヤー
	class Camera* camera_{};		// カメラ
	class Pendulum* pendulum_{};	// 振り子
	class Tile* tile_{};			// タイル
	class TestObject* test_object_{};
	class Robot* robot_{};

};

#endif  // STAGE1_1SCENE_H_