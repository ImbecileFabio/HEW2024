//==================================================
// [TutorialScene.cpp] チュートリアルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲーム説明や操作方法を表示するシーン
//==================================================

/*----- インクルード -----*/
#include "TutorialScene.h"

#include "../GameManager.h"
#include "../AudioManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TutorialScene::TutorialScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TutorialScene")
{
	camera_ = new Camera(game_manager_);
	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
TutorialScene::~TutorialScene()
{

}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void TutorialScene::Init()
{
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TutorialScene::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void TutorialScene::Update()
{
}