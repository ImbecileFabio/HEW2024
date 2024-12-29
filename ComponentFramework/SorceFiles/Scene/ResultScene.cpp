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
	game_manager_->RemoveGameObject(result_);
	game_manager_->RemoveGameObject(camera_);
	delete camera_;
	delete result_;
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void ResultScene::Init()
{
	std::function<void()> func = []() {};	// 初期化
	if (old_scene_name_ == "Stage1_1")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_2);
			};
	}
	if (old_scene_name_ == "Stage1_2")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_3);
			};
	}
	if (old_scene_name_ == "Stage1_3")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_4);
			};
	}
	if (old_scene_name_ == "Stage1_4")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_5);
			};
	}
	select_button_functions_[0] = [this]() {
		game_manager_->ChangeScene(SceneName::Title);
		};
	select_button_functions_[1] = [this, func]() {
		func();
		};
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void ResultScene::Uninit()
{
	delete camera_;
	delete result_;
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void ResultScene::Update()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_RIGHT))
		select_button_++;
	if (input.GetKeyTrigger(VK_LEFT))
		select_button_--;
	if (select_button_ > 1)	// 折り返し処理
		select_button_ = 0;
	if (select_button_ < 0)
		select_button_ = 1;
	
	if (input.GetKeyTrigger(VK_RETURN))
	{
		select_button_functions_[select_button_]();
	}
}
