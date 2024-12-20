//==================================================
// [TitleScene.cpp] タイトルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================

/*----- インクルード -----*/
#include "TitleScene.h"

#include "../GameManager.h"
#include "../AudioManager.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
{
	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
TitleScene::~TitleScene()
{
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void TitleScene::Init()
{
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TitleScene::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void TitleScene::Update()
{
	//game_manager_->GetAudioManager()->Play(SoundLabel_TitleBGM);
	if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		game_manager_->ChangeScene(SceneName::Stage1_1);
		//game_manager_->GetAudioManager()->Stop(SoundLabel_TitleBGM);
	}
}
