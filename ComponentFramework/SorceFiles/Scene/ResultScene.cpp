//==================================================
// [ResultScene.cpp] リザルトシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：リザルトを管理をするクラス
//==================================================

/*----- インクルード -----*/
#include "ResultScene.h"

#include "../GameManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
ResultScene::ResultScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "ResultScene")
{
	camera_ = new Camera(game_manager_);
	result_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/result/v01/10.JPG");
	result_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	result_->GetComponent<TransformComponent>()->SetPosition(0.0f, 0.0f);
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
