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
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"

int TitleScene::create_count = 0;
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
	, state_(State::title)
{
	select_stages_ = {};	// 0で初期化
	camera_ = new Camera(game_manager_);
	select_rough_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/7.JPG");
	select_rough_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	title_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/6.JPG");
	title_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	create_count++;
	if (create_count > 1)
	{
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
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
	//select_stages_[0][0] = game_manager_->ChangeScene(SceneName::Stage1_1);
	select_stages_[0][0] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_1);
		};
	select_stages_[0][1] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_2);
		};
	select_stages_[0][2] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_3);
		};
	select_stages_[0][3] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_4);
		};
	select_stages_[0][4] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_5);
		};
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TitleScene::Uninit()
{
	delete camera_;
	delete title_;
	delete select_rough_;
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void TitleScene::Update()
{
	auto& input = InputManager::GetInstance();
	//game_manager_->GetAudioManager()->Play(SoundLabel_TitleBGM);
	switch (state_)
	{
	case TitleScene::State::title:
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		if (input.GetKeyTrigger(VK_RETURN))// セレクトに移動
		{
			state_ = State::select;
		}
		break;
	case TitleScene::State::select:
		MoveSelect();
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		if (input.GetKeyTrigger(VK_RETURN))	// ゲームスタート
		{
			StageSelect();
			//game_manager_->GetAudioManager()->Stop(SoundLabel_TitleBGM);
		}
		if (input.GetKeyTrigger(VK_X))	// タイトル戻る
			state_ = State::title;
		break;
	case TitleScene::State::option:
		// ここにオプション
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
