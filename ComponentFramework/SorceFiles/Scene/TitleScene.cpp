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
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
	, state_(State::title)
{
	camera_ = new Camera(game_manager_);
	title_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/6.JPG");
	title_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	select_rough_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/7.JPG");
	select_rough_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);

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
	//game_manager_->GetAudioManager()->Play(SoundLabel_TitleBGM);
	switch (state_)
	{
	case TitleScene::State::title:
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))// セレクトに移動
		{
			state_ = State::select;
		}
		break;
	case TitleScene::State::select:
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))// ゲームスタート
		{
			game_manager_->ChangeScene(SceneName::Stage1_1);
			//game_manager_->GetAudioManager()->Stop(SoundLabel_TitleBGM);
		}
		if (InputManager::GetInstance().GetKeyTrigger(VK_X))	// タイトル戻る
		{
			state_ = State::title;
		}
		break;
	default:
		break;
	}
}
