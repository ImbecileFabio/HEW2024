//==================================================
// [Stage1_5Scene.h] ステージ1-5シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-5を管理をするクラス
//==================================================
#ifndef STAGE1_2SCENE_H_
#define STAGE1_2SCENE_H_
/*----- インクルード -----*/
#include "SceneBase.h"
//--------------------------------------------------
// ステージ1-5シーンクラス
//--------------------------------------------------
class Stage1_5Scene : public SceneBase
{
public:
	Stage1_5Scene(GameManager* _gameManager);
	~Stage1_5Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;
};
#endif // STAGE1_5SCENE_H_