//==================================================
// [Stage1_2Scene.h] ステージ1-2シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-2を管理をするクラス
//==================================================
#ifndef STAGE1_2SCENE_H_
#define STAGE1_2SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ1-2シーンクラス
//--------------------------------------------------
class Stage1_2Scene :  public SceneBase
{
public:
	Stage1_2Scene(GameManager* _gameManager);
	~Stage1_2Scene();

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
	STATE state_;


};

#endif // STAGE1_2SCENE_H_