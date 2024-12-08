//==================================================
// [ResultScene.h] リザルトシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================
#ifndef RESULT_SCENE_H_
#define RESULT_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"

//--------------------------------------------------
// リザルトシーンクラス
//--------------------------------------------------
class ResultScene :
	public SceneBase
{
public:
	ResultScene(GameManager* _gameManager);
	~ResultScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

};

#endif  // RESULT_SCENE_H_