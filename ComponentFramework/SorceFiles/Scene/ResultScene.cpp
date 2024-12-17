//==================================================
// [ResultScene.cpp] リザルトシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：リザルトを管理をするクラス
//==================================================

/*----- インクルード -----*/
#include "ResultScene.h"

#include "../GameManager.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
ResultScene::ResultScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "ResultScene")
{
	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
ResultScene::~ResultScene()
{
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void ResultScene::Init()
{
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void ResultScene::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void ResultScene::Update()
{
	if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		game_manager_->ChangeScene(SceneName::Title);
	}
}
