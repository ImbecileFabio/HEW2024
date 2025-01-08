//==================================================
// [TitleScene.cpp] タイトルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================

/*----- インクルード -----*/
#include "TitleScene.h"

#include "../GameManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Robot.h"

int TitleScene::create_count = 0;
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
	, state_(State::title)
{
	camera_ = new Camera(game_manager_);
	select_rough_ = new Revolution(game_manager_, "title_select");
	select_rough_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	title_ = new Revolution(game_manager_, "title_menu");
	title_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	title_buttons_[0] = new Revolution(game_manager_, "hoge");
	title_buttons_[1] = new Revolution(game_manager_, "hoge");
	title_buttons_[2] = new Revolution(game_manager_, "hoge");
	title_buttons_[0]->GetComponent<TransformComponent>()->SetSize(400.0f, 200.0f);
	title_buttons_[1]->GetComponent<TransformComponent>()->SetSize(400.0f, 200.0f);
	title_buttons_[2]->GetComponent<TransformComponent>()->SetSize(400.0f, 200.0f);
	title_buttons_[0]->GetComponent<TransformComponent>()->SetPosition(-400.0f, -300.0f);
	title_buttons_[1]->GetComponent<TransformComponent>()->SetPosition(0.0f, -300.0f);
	title_buttons_[2]->GetComponent<TransformComponent>()->SetPosition(400.0f, -300.0f);

	create_count++;
	if (create_count > 1)
	{
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		for (auto& title_button : title_buttons_)
			title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		state_ = State::select;
	}

	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
TitleScene::~TitleScene()
{
	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void TitleScene::Init()
{
	select_stages_[0][0] = [this]() {
		game_manager_->ChangeScene(SceneName::Stage1_1);
		};
	select_stages_[0][1] = [this]() {
		game_manager_->ChangeScene(SceneName::Stage1_2);
		};
	select_stages_[0][2] = [this]() {
		game_manager_->ChangeScene(SceneName::Stage1_3);
		};
	select_stages_[0][3] = [this]() {
		game_manager_->ChangeScene(SceneName::Stage1_4);
		};
	select_stages_[0][4] = [this]() {
		game_manager_->ChangeScene(SceneName::Stage1_5);
		};
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
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case TitleScene::State::title:
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// タイトルを表示
		for (auto& title_button : title_buttons_)	// ボタンを表示
			title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		if (input.GetKeyTrigger(VK_RIGHT))			// 左右移動
			title_select_button_++;
		if (input.GetKeyTrigger(VK_LEFT))
			title_select_button_--;
		if (title_select_button_ > 2)				// 折り返し処理
			title_select_button_ = 0;
		if (title_select_button_ < 0)
			title_select_button_ = 2;
		// 全ボタンの色を更新
		for (int i = 0; i < title_buttons_.size(); ++i)
		{
			if (i == title_select_button_)
			{
				// 選択中のボタンの色を変更
				title_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
			}
			else
			{
				// 未選択のボタンの色を元に戻す
				title_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			}
		}

		if (input.GetKeyTrigger(VK_RETURN))	// 決定
		{
			switch (title_select_button_)
			{
			case 0:
				state_ = State::select;		// セレクトに移動
				for (auto& title_button : title_buttons_)	// ボタンを非表示に
					title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
				break;
			case 1:
				state_ = State::end;
				break;
			default:
				break;
			}
		}
		break;
	case TitleScene::State::select:
		MoveSelect();
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		if (input.GetKeyTrigger(VK_RETURN))	// ゲームスタート
		{
			StageSelect();
		}
		if (input.GetKeyTrigger(VK_X))	// タイトル戻る
			state_ = State::title;
		break;
	case TitleScene::State::option:
		// ここにオプション
		break;
	case TitleScene::State::end:
		game_manager_->SetEndFlag(true);
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// 二次元配列の状態によってステージを選ぶ
//--------------------------------------------------
void TitleScene::StageSelect()
{
	select_stages_[chapter_][stage_]();	// 添え字によってChangeSceneを呼びだす
}
//--------------------------------------------------
// セレクトの添え字の動きを管理する関数
//--------------------------------------------------
void TitleScene::MoveSelect()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_R))		// Rボタン
		chapter_++;
	if (input.GetKeyTrigger(VK_L))		// Lボタン
		chapter_--;
	if (input.GetKeyTrigger(VK_RIGHT))	// 右
		stage_++;
	if (input.GetKeyTrigger(VK_LEFT))	// 左
		stage_--;
	// 範囲外の処理
	if (chapter_ > CHAPTER_MAX) chapter_ = 0;
	if (chapter_ < 0) chapter_ = 0;
	if (stage_ < 0) stage_ = 4;
	if (stage_ > STAGE_MAX) stage_ = 0;
}
