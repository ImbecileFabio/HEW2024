//==================================================
// [TitleScene.h] タイトルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"

//--------------------------------------------------
// タイトルシーンクラス
//--------------------------------------------------
class TitleScene :
    public SceneBase
{
public:
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	Sound sound;
};

#endif  // TITLE_SCENE_H_