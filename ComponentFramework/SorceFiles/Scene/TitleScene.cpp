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
#include "../GameObjects/GameObject/Robot.h"

int TitleScene::create_count = 0;
//#define ControllerPlay
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
	, state_(State::title)
{
	camera_ = new Camera(game_manager_);
	// タイトル・セレクトの背景
	backdrop_ = new Revolution(game_manager_, "result_backdrop", "BackDrop", 10);
	backdrop_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	// タイトル画面のボタン背景（リボン）
	title_ribbon_ = new Revolution(game_manager_, "title_ribbon", "TitleRibbon");
	title_ribbon_->GetTransformComponent()->SetSize(1920.0f, 1000.0f);
	title_ribbon_->GetTransformComponent()->SetPosition(0.0f, -48.0f);
	// タイトルロゴ
	title_logo_ = new Revolution(game_manager_, "title_logo", "TitleLogo");
	title_logo_->GetTransformComponent()->SetSize(761.0f, 777.0f);
	title_logo_->GetTransformComponent()->SetPosition(580.0f, 210.0f);
	// タイトル画面のボタン(Option, Start, End)
	title_buttons_[0] = new Revolution(game_manager_, "title_option", "TitleOption_Button");
	title_buttons_[1] = new Revolution(game_manager_, "title_start", "TitleStart_Button");
	title_buttons_[2] = new Revolution(game_manager_, "title_end", "TitleEnd_Button");	title_buttons_[0]->GetTransformComponent()->SetSize(400.0f, 400.0f);
	title_buttons_[0]->GetTransformComponent()->SetSize(400.0f, 400.0f);
	title_buttons_[1]->GetTransformComponent()->SetSize(349.0f, 340.0f);
	title_buttons_[2]->GetTransformComponent()->SetSize(278.0f, 255.0f);
	title_buttons_[0]->GetTransformComponent()->SetPosition(-589.0f, -375.0f);
	title_buttons_[1]->GetTransformComponent()->SetPosition(15.0f, -381.0f);
	title_buttons_[2]->GetTransformComponent()->SetPosition(555.0f, -387.0f);
	title_buttons_[0]->GetTransformComponent()->SetPosition(-589.0f, -343.0f);
	title_buttons_[1]->GetTransformComponent()->SetPosition(15.0f, -349.0f);
	title_buttons_[2]->GetTransformComponent()->SetPosition(555.0f, -355.0f);
	// タイトル画面のカーソル
	title_cursor_ = new Revolution(game_manager_, "title_cursor", "TitleCursor");
	title_cursor_->GetTransformComponent()->SetSize(151.0f, 137.0f);
	title_cursor_->GetTransformComponent()->SetPosition(-834.0f, -342.0f);
	// セレクト画面のLB・RBボタン
	select_left_button_ = new Revolution(game_manager_, "stageselect_left", "StageSelectLeft");
	select_right_button_ = new Revolution(game_manager_, "stageselect_right", "StageSelectRight");
	select_left_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_right_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_right_button_->GetTransformComponent()->SetPosition(-828.0f, 423.0f);
	select_left_button_->GetTransformComponent()->SetPosition(828.0f, 421.0f);
	select_left_button_->GetTransformComponent()->SetSize(215.0f, 215.0f);
	select_right_button_->GetTransformComponent()->SetSize(228.0f, 228.0f);
	// セレクト画面のチャプターナンバー画像
	select_chapter_left = new Revolution(game_manager_, "stageselect_chapter", "StageSelectChapterLeft");
	select_chapter_right = new Revolution(game_manager_, "stageselect_chapter", "StageSelectChapterRight");
	select_chapter_center = new Revolution(game_manager_, "stageselect_chapter", "StageSelectChapterCenter");
	select_chapter_left->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_chapter_right->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_chapter_center->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// オプションボタン・戻るボタン
	select_chapter_left->GetTransformComponent()->SetSize(380.0f, 380.0f);
	select_chapter_right->GetTransformComponent()->SetSize(380.0f, 380.0f);
	select_chapter_center->GetTransformComponent()->SetSize(380.0f, 380.0f);
	select_chapter_center->GetTransformComponent()->SetPosition(0.0f, 421.0f);
	select_chapter_left->GetTransformComponent()->SetPosition(-519.0f, 421.0f);
	select_chapter_right->GetTransformComponent()->SetPosition(519.0f, 421.0f);

	select_option_button_ = new Revolution(game_manager_, "stageselect_option");
	select_return_button_ = new Revolution(game_manager_, "stageselect_return");
	select_option_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_return_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_option_button_->GetTransformComponent()->SetPosition(842.0f, 246.0f);
	select_return_button_->GetTransformComponent()->SetPosition(-842.0f, 246.0f);
	select_option_button_->GetTransformComponent()->SetSize(200.0f, 200.0f);
	select_return_button_->GetTransformComponent()->SetSize(200.0f, 200.0f);
	// オプション画面
	option_images_[0] = new Revolution(game_manager_, "option_window", "option_window",11);
	option_images_[0]->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	option_images_[1] = new Revolution(game_manager_, "option_return", "option_return", 12);
	option_images_[1]->GetTransformComponent()->SetSize(256.0f, 256.0f);
	option_images_[1]->GetTransformComponent()->SetPosition(621.0f, -354.0f);
	option_images_[2] = new Revolution(game_manager_, "option_frame_slider", "option_frame_slider", 13);
	option_images_[2]->GetTransformComponent()->SetSize(1100.0f, 723.0f);
	option_images_[2]->GetTransformComponent()->SetPosition(205.0f, 184.0f);
	option_images_[3] = new Revolution(game_manager_, "option_bgm_button", "option_bgm_button", 14);
	option_images_[3]->GetTransformComponent()->SetSize(340.0f, 340.0f);
	option_images_[3]->GetTransformComponent()->SetPosition(-628.0f, 177.0f);
	option_images_[4] = new Revolution(game_manager_, "option_se_button", "option_se_button", 14);
	option_images_[4]->GetTransformComponent()->SetSize(340.0f, 340.0f);
	option_images_[4]->GetTransformComponent()->SetPosition(-628.0f, -118.0f);
	option_images_[5] = new Revolution(game_manager_, "option_arrow_right", "option_arrow_right", 14);
	option_images_[5]->GetTransformComponent()->SetSize(128.0f, 124.0f);
	option_images_[5]->GetTransformComponent()->SetPosition(808.0f, 183.0f);
	option_images_[6] = new Revolution(game_manager_, "option_arrow_left", "option_arrow_left", 14);
	option_images_[6]->GetTransformComponent()->SetSize(128.0f, 124.0f);
	option_images_[6]->GetTransformComponent()->SetPosition(-397.0f, 183.0f);
	option_images_[7] = new Revolution(game_manager_, "option_frame_slider", "option_frame_slider", 13);
	option_images_[7]->GetTransformComponent()->SetSize(1100.0f, 723.0f);
	option_images_[7]->GetTransformComponent()->SetPosition(205.0f, -119.0f);
	option_images_[8] = new Revolution(game_manager_, "option_arrow_right", "option_arrow_right", 14);
	option_images_[8]->GetTransformComponent()->SetSize(128.0f, 124.0f);
	option_images_[8]->GetTransformComponent()->SetPosition(808.0f, -119.0f);
	option_images_[9] = new Revolution(game_manager_, "option_arrow_left", "option_arrow_left", 14);
	option_images_[9]->GetTransformComponent()->SetSize(128.0f, 124.0f);
	option_images_[9]->GetTransformComponent()->SetPosition(-397.0f, -121.0f);

	// オプション画面のボールスライダーとカラースティック
	option_ball_slider_bgm_ = new Revolution(game_manager_, "option_ball_slider", "option_ball_slider", 16);
	option_ball_slider_bgm_->GetTransformComponent()->SetSize(256.0f, 256.0f);
	option_ball_slider_bgm_->GetTransformComponent()->SetPosition(0.0f, 187.0f);
	option_ball_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	option_stick_slider_bgm_ = new Revolution(game_manager_, "option_stick_slider", "option_stick_slider", 15);
	option_stick_slider_bgm_->GetTransformComponent()->SetSize(1100.0f, 750.0f);
	option_stick_slider_bgm_->GetTransformComponent()->SetPosition(205.0f, 184.0f);
	option_stick_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	option_ball_slider_se_ = new Revolution(game_manager_, "option_ball_slider", "option_ball_slider", 16);
	option_ball_slider_se_->GetTransformComponent()->SetPosition(0.0f, -121.0f);
	option_ball_slider_se_->GetTransformComponent()->SetSize(256.0f, 256.0f);
	option_ball_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	option_stick_slider_se_ = new Revolution(game_manager_, "option_stick_slider", "option_stick_slider", 15);
	option_stick_slider_se_->GetTransformComponent()->SetSize(1100.0f, 750.0f);
	option_stick_slider_se_->GetTransformComponent()->SetPosition(205.0f, -120.0f);
	option_stick_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	// セレクト画面のステージナンバー
//select_numbers_s_ = new Revolution(game_manager_, "stageselect_stage_numbers_s", "StageNumber_S");
	select_numbers_m_left_ = new Revolution(game_manager_, "stageselect_stage_numbers_m", "StageNumber_M_Left_");
	select_numbers_m_left_->GetTransformComponent()->SetPosition(-653.0f, -131.0f);
	select_numbers_m_right_ = new Revolution(game_manager_, "stageselect_stage_numbers_m", "StageNumber_M_Right_");
	select_numbers_m_right_->GetTransformComponent()->SetPosition(653.0f, -134.0f);
	select_numbers_w_ = new Revolution(game_manager_, "stageselect_stage_numbers_w", "StageNumber_W");
	//select_numbers_s_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_numbers_m_left_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_numbers_m_right_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	select_numbers_w_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	//select_numbers_s_->GetTransformComponent()->SetSize(512.0f, 512.0f);
	select_numbers_m_left_->GetTransformComponent()->SetSize(512.0f, 512.0f);
	select_numbers_m_right_->GetTransformComponent()->SetSize(512.0f, 512.0f);
	select_numbers_w_->GetTransformComponent()->SetSize(830.0f, 830.0f);
	select_numbers_w_->GetTransformComponent()->SetPosition(9.0f, -52.0f);

	for (auto& option_image : option_images_)
		option_image->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

	create_count++;
	// 一回でもタイトルが生成されていたら、ステージから戻ったときにセレクト画面にする処理
	if (create_count > 1)
	{
		for (auto& title_button : title_buttons_)
			title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		title_ribbon_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		title_logo_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		title_cursor_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		select_chapter_left->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		select_chapter_right->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		select_chapter_center->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		select_option_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// オプションボタンを表示
		select_return_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// 戻るボタンを表示
		select_left_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// LBボタンを表示
		select_right_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// RBボタンを表示
		select_numbers_m_left_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		select_numbers_m_right_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		select_numbers_w_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
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
	// 二次元配列にシーン情報を保存しておく
	select_stages_[0][0] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage1_1);
		};
	select_stages_[0][1] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage1_2);
		};
	select_stages_[0][2] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage1_3);
		};
	select_stages_[0][3] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage1_4);
		};
	select_stages_[1][0] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage2_1);
		};
	select_stages_[1][1] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage2_2);
		};
	select_stages_[1][2] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage2_3);
		};
	select_stages_[1][3] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage2_4);
		};
	select_stages_[2][0] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage3_1);
		};
	select_stages_[2][1] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage3_2);
		};
	select_stages_[2][2] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage3_3);
		};
	select_stages_[2][3] = [this]() {
		game_manager_->TransitionToScene(SceneName::Stage3_4);
		};

	AudioManager::GetInstance()->Play(SoundLabel_TitleBGM);
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TitleScene::Uninit()
{
	AudioManager::GetInstance()->Stop(SoundLabel_TitleBGM);
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
		backdrop_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// タイトルを表示
		title_ribbon_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// リボンを表示に
		title_logo_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// ロゴを表示に
		title_cursor_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// カーソルを表示に
		for (auto& title_button : title_buttons_)	// ボタンを表示
			title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		// 左右移動
//#ifdef ControllerPlay
//#else
		if (input.GetKeyTrigger(VK_RIGHT)) {
			title_select_button_++;
			AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
		}
		if (input.GetKeyTrigger(VK_LEFT)) {
			title_select_button_--;
			AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
		}
		if (title_select_button_ > 2)				// 折り返し処理
			title_select_button_ = 0;
		if (title_select_button_ < 0)
			title_select_button_ = 2;
		// 全ボタンの色を更新
		for (int i = 0; i < title_buttons_.size(); ++i)
		{
			if (i == title_select_button_)
			{
				switch (i)
				{
				case 0:
					title_cursor_->GetTransformComponent()->SetPosition(-834.0f, -342.0f);
					break;
				case 1:
					title_cursor_->GetTransformComponent()->SetPosition(-207.0f, -342.0f);
					break;
				case 2:
					title_cursor_->GetTransformComponent()->SetPosition(356.0f, -342.0f);
					break;
				default:
					break;
				}
			}
		}

		if (input.GetKeyTrigger(VK_RETURN))	// 決定
		{
			switch (title_select_button_)
			{
			case 0:	// オプション
				state_ = State::option;		// オプションに移動
				// タイトル画面のオブジェクトを非表示に
				title_ribbon_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// リボンを非表示に
				title_logo_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// ロゴを非表示に
				title_cursor_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// カーソルを非表示に
				for (auto& title_button : title_buttons_)	// ボタンを非表示に
					title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
				for (auto& option_image : option_images_)
					option_image->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				option_ball_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				option_ball_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				option_stick_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				option_stick_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);

				AudioManager::GetInstance()->Play(SoundLabel_UIDecisionSE);
				break;
			case 1:	// セレクト画面に移動
				state_ = State::select;		// セレクトに移動
				title_ribbon_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// リボンを非表示に
				title_logo_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// ロゴを非表示に
				title_cursor_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// カーソルを非表示に
				for (auto& title_button : title_buttons_)	// ボタンを非表示に
					title_button->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
				select_option_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// オプションボタンを表示
				select_return_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// 戻るボタンを表示
				select_left_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// LBボタンを表示
				select_right_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);	// RBボタンを表示
				select_chapter_center->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				select_chapter_right->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				select_chapter_left->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				//select_numbers_s_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				select_numbers_m_left_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				select_numbers_m_right_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				select_numbers_w_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
				break;
			case 2:	// ゲーム終了
				state_ = State::end;
				AudioManager::GetInstance()->Play(SoundLabel_UIDecisionSE);
				break;
			default:
				break;
			}
		}
		break;
	case TitleScene::State::select:
		MoveSelect();						// セレクトの添え字の動きを管理
		if (input.GetKeyTrigger(VK_RETURN))	// ゲームスタート
		{
			StageSelect();
		}
		if (input.GetKeyTrigger(VK_X))		// タイトル戻る
		{
			state_ = State::title;
			select_option_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// オプションボタンを表示
			select_return_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// 戻るボタンを表示
			select_left_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// LBボタンを表示
			select_right_button_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);	// RBボタンを表示
			select_chapter_center->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			select_chapter_right->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			select_chapter_left->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			//select_numbers_s_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			select_numbers_m_left_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			select_numbers_m_right_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			select_numbers_w_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

			AudioManager::GetInstance()->Play(SoundLabel_UICancelSE);
		}
		break;
	case TitleScene::State::option:
		// ここにオプション
		if (input.GetKeyTrigger(VK_X))		// タイトル戻る
		{
			state_ = State::title;
			for (auto& option_image : option_images_)
				option_image->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			option_ball_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			option_ball_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			option_stick_slider_bgm_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			option_stick_slider_se_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			
			AudioManager::GetInstance()->Play(SoundLabel_UICancelSE);
		}
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
	DirectX::SimpleMath::Vector2 frameSize = select_chapter_center->GetComponent<SpriteComponent>()->GetTexture().get()->GetFrameSize();
	DirectX::SimpleMath::Vector2 numberFrameSize = select_numbers_m_left_->GetComponent<SpriteComponent>()->GetTexture().get()->GetFrameSize();
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_E))		// Rボタン
	{
		chapter_++;
		stage_ = 0;	// 章が変わったらステージをリセット
		AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
	}
	if (input.GetKeyTrigger(VK_Q))		// Lボタン
	{
		chapter_--;
		stage_ = 0;	// 章が変わったらステージをリセット
		AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
	}
	if (input.GetKeyTrigger(VK_RIGHT)) {	// 右
		stage_++;
		AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
	}
	if (input.GetKeyTrigger(VK_LEFT)) {		// 左
		stage_--;
		AudioManager::GetInstance()->Play(SoundLabel_UICursorMoveSE);
	}
		
	if (chapter_ == 0)
	{
		select_chapter_center->GetComponent<SpriteComponent>()->SetUV({ 3.0f * frameSize.x, 0.0f * frameSize.y });
		select_chapter_left->GetComponent<SpriteComponent>()->SetUV({ 2.0f * frameSize.x, 0.0f * frameSize.y });
		select_chapter_right->GetComponent<SpriteComponent>()->SetUV({ 1.0f * frameSize.x, 0.0f * frameSize.y });
		switch (stage_)
		{
		case 0:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			break;
		case 1:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			break;
		case 2:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			break;
		case 3:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 0.0f * numberFrameSize.y });
			break;
		default:
			break;
		}
	}
	else if (chapter_ == 1)
	{
		select_chapter_center->GetComponent<SpriteComponent>()->SetUV({ 0.0f * frameSize.x, 1.0f * frameSize.y });
		select_chapter_left->GetComponent<SpriteComponent>()->SetUV({ 0.0f * frameSize.x, 0.0f * frameSize.y });
		select_chapter_right->GetComponent<SpriteComponent>()->SetUV({ 2.0f * frameSize.x, 0.0f * frameSize.y });
		switch (stage_)
		{
		case 0:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			break;
		case 1:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			break;
		case 2:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			break;
		case 3:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 1.0f * numberFrameSize.y });
			break;
		default:
			break;
		}
	}
	else if (chapter_ == 2)
	{
		select_chapter_center->GetComponent<SpriteComponent>()->SetUV({ 1.0f * frameSize.x, 1.0f * frameSize.y });
		select_chapter_left->GetComponent<SpriteComponent>()->SetUV({ 1.0f * frameSize.x, 0.0f * frameSize.y });
		select_chapter_right->GetComponent<SpriteComponent>()->SetUV({ 0.0f * frameSize.x, 0.0f * frameSize.y });
		switch (stage_)
		{
		case 0:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			break;
		case 1:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			break;
		case 2:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 3.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			break;
		case 3:
			select_numbers_w_->GetComponent<SpriteComponent>()->SetUV({ 1.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			select_numbers_m_left_->GetComponent<SpriteComponent>()->SetUV({ 0.0f * numberFrameSize.x, 3.0f * numberFrameSize.y });
			select_numbers_m_right_->GetComponent<SpriteComponent>()->SetUV({ 2.0f * numberFrameSize.x, 2.0f * numberFrameSize.y });
			break;
		default:
			break;
		}
	}
	// 範囲外の処理
	if (chapter_ > CHAPTER_MAX)
	{
		chapter_ = 0;
	}
	if (chapter_ < 0)
	{
		chapter_ = 3;
	}
	if (stage_ < 0)
	{
		stage_ = 3;
	}
	if (stage_ > STAGE_MAX)
	{
		stage_ = 0;
	}
}
