//==================================================
// [SceneBase.cpp] シーンベースクラス
// 著者：有馬啓太
//--------------------------------------------------
// 説明：シーンの基底クラス
//==================================================

/*----- インクルード -----*/
#include <memory>
#include "SceneBase.h"

#include "../GameObjects/GameObject/Revolution.h"
#include "../GameManager.h"
#include "../TileMapManager.h"
#include "../InputManager.h"
#include "../PemdulumManager.h"
#include "../AudioManager.h"
//--------------------------------------------------
// @param	_gameManager シーンの所有者, _sceneName シーン名
// @brief	コンストラクタ
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// 所有者
	, scene_name_(_sceneName)		// シーン名
{
	tile_map_manager_ = std::make_unique<TileMapManager>(game_manager_);

	stageUIs_[0] = new Revolution(game_manager_, "stageUI", "stageUI",180);
	stageUIs_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	stageUIs_[0]->GetTransformComponent()->SetPosition(-702.0f, 365.0f);
	stageUIs_[0]->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	stageUIs_[1] = new Revolution(game_manager_, "pause_button", "pause_button", 170);
	stageUIs_[1]->GetTransformComponent()->SetSize(128.0f, 128.0f);
	stageUIs_[1]->GetTransformComponent()->SetPosition(861.0f, 445.0f);
	stageUIs_[1]->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

	gearMax_ = new Revolution(game_manager_, "numbers", "gearMax", 181);
	gearMax_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearMax_->GetTransformComponent()->SetPosition(-551.0f, 412.0f);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	gearGet_ = new Revolution(game_manager_, "numbers", "gearGet", 181);
	gearGet_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearGet_->GetTransformComponent()->SetPosition(-677.0f, 454.0f);
	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	hammerNum_ = new Revolution(game_manager_, "numbers", "hammerNum", 181);
	hammerNum_->GetTransformComponent()->SetPosition(-596.0f, 290.0f);
	hammerNum_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

	pauseWindow_ = new Revolution(game_manager_, "pose_window", "pose_window", 200);
	pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pauseWindow_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pause_instruction_ = new Revolution(game_manager_, "instruction_window", "instruction_window", 210);
	pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pause_instruction_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pauseButtons_[0] = new Revolution(game_manager_, "pose_return_game","pose_return_game", 201);
	pauseButtons_[1] = new Revolution(game_manager_, "pose_restart", "pose_restart", 201);
	pauseButtons_[2] = new Revolution(game_manager_, "pose_select", "pose_select", 201);
	pauseButtons_[3] = new Revolution(game_manager_, "pose_instruction", "pose_instruction", 201);
	pauseButtons_[0]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[0]->GetTransformComponent()->SetPosition(0.0f, 275.0f);
	pauseButtons_[1]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[1]->GetTransformComponent()->SetPosition(0.0f, 101.0f);
	pauseButtons_[2]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[2]->GetTransformComponent()->SetPosition(0.0f, -76.0f);
	pauseButtons_[3]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[3]->GetTransformComponent()->SetPosition(0.0f, -252.0f);
	//pauseButtons_[4]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	//pauseButtons_[4]->GetTransformComponent()->SetPosition(0.0f, -252.0f);
	for(auto& it : pauseButtons_)
		it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
}

SceneBase::~SceneBase()
{

}

void SceneBase::PauseWindow()
{
	// ここで操作を記述
	auto& input = InputManager::GetInstance();
	// ウィンドウが更に開いていないときだけボタン操作を実行
	if (!isWindowOpen)
	{
		if (input.GetKeyTrigger(VK_UP) || input.GetButtonTrigger(XINPUT_UP))				// 上下移動
			pause_select_button_--;
		if (input.GetKeyTrigger(VK_DOWN) || input.GetButtonTrigger(XINPUT_DOWN))
			pause_select_button_++;
		if (pause_select_button_ >= 4)				// 折り返し処理
			pause_select_button_ = 0;
		if (pause_select_button_ < 0)
			pause_select_button_ = 3;
	}
	else
	{
		if (input.GetKeyTrigger(VK_X) || input.GetButtonTrigger(XINPUT_B))
		{
			if (pause_select_button_ == 3) 
			{
				isWindowOpen = false;
				pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
		}
	}
	// 選択中のボタンに色の変化をつける処理
	for (int i = 0; i < pauseButtons_.size(); ++i)
	{
		if (i == pause_select_button_)
		{
			// 選択中のボタンの色を変更
			pauseButtons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
		}
		else
		{
			// 未選択のボタンの色を元に戻す
			pauseButtons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	// 現在選択されている添え字によって決定処理を変更
	if (input.GetKeyTrigger(VK_RETURN) || input.GetButtonTrigger(XINPUT_A))
	{
		switch (pause_select_button_)
		{
		case 0:	// ゲーム画面に戻る
			stageState_ = StageState::Game;
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Active);	// 稼働コンテナのオブジェクトを全で稼働状態に
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			pauseWindow_	  ->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			break;
		case 1:	// リスタート
			stageState_ = StageState::Rewind;
			break;
		case 2:	// セレクト画面に戻る
			game_manager_->ResetItemCount();
			game_manager_->ChangeScene(SceneName::Title);
			AudioManager::GetInstance()->Stop(SoundLabel_StageBGM);
			break;
		case 3:	// 操作説明を表示
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			isWindowOpen = true;
			break;
		default:
			break;
		}
	}
}

void SceneBase::OptionWindow()
{

}

void SceneBase::NumberChange()
{
	// ギアのMAX個数を表示
	auto gearSpriteComponent = gearMax_->GetComponent<SpriteComponent>();
	// ギアの取得状態を表示
	auto gearGetSpriteComponent = gearGet_->GetComponent<SpriteComponent>();
	// ハンマーの叩ける回数を表示
	auto hammerSpriteComponent = hammerNum_->GetComponent<SpriteComponent>();
	// ギアのMAX個数によってUVを変更
	DirectX::SimpleMath::Vector2 frameSize = gearSpriteComponent->GetTexture().get()->GetFrameSize();
	gearSpriteComponent->SetUV({ gearMaxCount_ * frameSize.x, 0.0f * frameSize.y });
	gearGetSpriteComponent->SetUV({ game_manager_->GetItemCount() * frameSize.x, 0.0f * frameSize.y });
	// ハンマーの叩ける回数によってUVを変更
	switch (hammerMaxCount_)
	{
	case 0:
		hammerSpriteComponent->SetUV({ 0.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 1:
		hammerSpriteComponent->SetUV({ 1.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 2:
		hammerSpriteComponent->SetUV({ 2.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 3:
		hammerSpriteComponent->SetUV({ 3.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 4:
		hammerSpriteComponent->SetUV({ 0.0f * frameSize.x, 1.0f * frameSize.y});
		break;
	case 5:
		hammerSpriteComponent->SetUV({ 1.0f * frameSize.x, 1.0f * frameSize.y});
		break;
	case 6:
		hammerSpriteComponent->SetUV({ 2.0f * frameSize.x, 1.0f * frameSize.y});
		break;
	case 7:
		hammerSpriteComponent->SetUV({ 3.0f * frameSize.x, 1.0f * frameSize.y});
		break;
	case 8:
		hammerSpriteComponent->SetUV({ 0.0f * frameSize.x, 2.0f * frameSize.y});
		break;
	case 9:
		hammerSpriteComponent->SetUV({ 1.0f * frameSize.x, 2.0f * frameSize.y});
		break;
	}
	if (hammerMaxCount_ == 0)
	{
		isHammerMax_ = true;
	}
}

