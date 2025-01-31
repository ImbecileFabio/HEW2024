//==================================================
// [TutorialScene.h] チュートリアルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：チュートリアルの管理をするクラス
//==================================================
#ifndef TUTORIAL_SCENE_H_
#define TUTORIAL_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"
#include <array>
/*----- 前方宣言 -----*/
class Revolution;
//--------------------------------------------------
// リザルトシーンクラス
//--------------------------------------------------
class TutorialScene:
	public SceneBase
{
public:
	TutorialScene(GameManager* _gameManager);
	~TutorialScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	class Camera* camera_{};	// カメラ

};

#endif  // TUTORIAL_SCENE_H_