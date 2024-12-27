//==================================================
// [Stage1_3Scene.h] ステージ1-3シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-3を管理をするクラス
//==================================================
#ifndef STAGE1_3SCENE_H_
#define STAGE1_3SCENE_H_
/*----- インクルード -----*/
#include "SceneBase.h"
//--------------------------------------------------
// ステージ1-3シーンクラス
//--------------------------------------------------
class Stage1_3Scene : public SceneBase
{
public:
	Stage1_3Scene(GameManager* _gameManager);
	~Stage1_3Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;
};

#endif // STAGE1_3SCENE_H_