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

#define CONTROLLER
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TutorialScene::TutorialScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TutorialScene")
{
	camera_ = new Camera(game_manager_);
	tutorial_scene_ = new Revolution(game_manager_, "tutorial_01");
	tutorial_play_ = new Revolution(game_manager_, "tutorial_02");

	tutorial_scene_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);
	tutorial_play_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	tutorial_play_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
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
	std::function<void()> func = []() {};	// 初期化
	if (next_scene_name_ == SceneName::Stage1_1)	// リザルトの前のシーンによって次のシーンを変更
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage1_1);
			};
	}
	if (next_scene_name_ == SceneName::Stage1_2)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage1_2);
			};
	}
	if (next_scene_name_ == SceneName::Stage1_3)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage1_3);
			};
	}
	if (next_scene_name_ == SceneName::Stage1_4)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage1_4);
			};
	}
	if (next_scene_name_ == SceneName::Stage2_1)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage2_1);
			};
	}
	if (next_scene_name_ == SceneName::Stage2_2)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage2_2);
			};
	}
	if (next_scene_name_ == SceneName::Stage2_3)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage2_3);
			};
	}
	if (next_scene_name_ == SceneName::Stage2_4)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage2_4);
			};
	}
	if (next_scene_name_ == SceneName::Stage3_1)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage3_1);
			};
	}
	if (next_scene_name_ == SceneName::Stage3_2)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage3_2);
			};
	}
	if (next_scene_name_ == SceneName::Stage3_3)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage3_3);
			};
	}
	if (next_scene_name_ == SceneName::Stage3_4)
	{
		func = [this]() {
			game_manager_->TransitionToScene(SceneName::Stage3_4);
			};
	}
	next_scene_ = [func]() {	// ifの結果を代入
		func();
		};
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
	auto& input = InputManager::GetInstance();
	// 次へ
	if (input.GetKeyTrigger(VK_RETURN) || input.GetButtonTrigger(XINPUT_A))
	{
		if (tutorial_play_->GetComponent<RenderComponent>()->GetState() == RenderComponent::State::draw)
		{
			next_scene_();	// 次のシーンへ遷移
		}
		else if(tutorial_play_->GetComponent<RenderComponent>()->GetState() == RenderComponent::State::notDraw)
		{
			tutorial_play_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			tutorial_scene_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		}
	}
	// 戻る
	if (input.GetButtonTrigger(XINPUT_B) || input.GetKeyTrigger(VK_X))
	{
		if (tutorial_play_->GetComponent<RenderComponent>()->GetState() == RenderComponent::State::draw)
		{
			tutorial_play_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			tutorial_scene_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		}
	}

}