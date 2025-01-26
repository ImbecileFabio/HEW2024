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
	backdrop_ = new Revolution(game_manager_, "result_backdrop", "result_backdrop");
	backdrop_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_ribbon_ = new Revolution(game_manager_, "result_front_ribbon", "result_front_ribbon");
	result_ribbon_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_buttons_[0] = new Revolution(game_manager_, "result_select", "result_select");
	result_buttons_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[0]->GetTransformComponent()->SetPosition(-443.0f, -300.0f);
	result_buttons_[1] = new Revolution(game_manager_, "result_next", "result_next");
	result_buttons_[1]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[1]->GetTransformComponent()->SetPosition(464.0f, -300.0f);

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
	std::function<void()> func = []() {};	// 初期化
	if (old_scene_name_ == "Stage1_1")	// リザルトの前のシーンによって次のシーンを変更
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
	select_button_functions_[0] = [this]() {	// ボタンに関数を登録
		game_manager_->ChangeScene(SceneName::Title);
		};
	select_button_functions_[1] = [func]() {	// ifの結果を代入
		func();
		};

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
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_RIGHT))
		select_button_++;
	if (input.GetKeyTrigger(VK_LEFT))
		select_button_--;
	if (select_button_ > 1)	// 折り返し処理
		select_button_ = 0;
	if (select_button_ < 0)
		select_button_ = 1;
	// 全ボタンの色を更新
	for (int i = 0; i < result_buttons_.size(); ++i)
	{
		if (i == select_button_)
		{
			// 選択中のボタンの色を変更
			result_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
		}
		else
		{
			// 未選択のボタンの色を元に戻す
			result_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	if (input.GetKeyTrigger(VK_RETURN))
	{
		select_button_functions_[select_button_]();	// ボタンの関数を実行
	}

}
