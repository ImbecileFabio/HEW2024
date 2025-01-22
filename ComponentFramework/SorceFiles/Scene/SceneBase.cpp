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
//--------------------------------------------------
// @param	_gameManager シーンの所有者, _sceneName シーン名
// @brief	コンストラクタ
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// 所有者
	, scene_name_(_sceneName)		// シーン名
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
	tile_map_manager_ = std::make_unique<TileMapManager>(game_manager_);

	stageUIs_[0] = new Revolution(game_manager_, "stageUI", 2);
	stageUIs_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	stageUIs_[0]->GetTransformComponent()->SetPosition(-702.0f, 365.0f);
	stageUIs_[1] = new Revolution(game_manager_, "pause_button", 2);
	stageUIs_[1]->GetTransformComponent()->SetSize(128.0f, 128.0f);
	stageUIs_[1]->GetTransformComponent()->SetPosition(861.0f, 445.0f);

	gearMax_ = new Revolution(game_manager_, "numbers");
	gearMax_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearMax_->GetTransformComponent()->SetPosition(-551.0f, 412.0f);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	gearGet_ = new Revolution(game_manager_, "numbers");
	gearGet_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearGet_->GetTransformComponent()->SetPosition(-677.0f, 454.0f);
	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	hammerNum_ = new Revolution(game_manager_, "numbers");
	hammerNum_->GetTransformComponent()->SetPosition(-596.0f, 290.0f);
	hammerNum_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

	pauseWindow_ = new Revolution(game_manager_, "pose_window");
	pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pauseWindow_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pause_instruction_ = new Revolution(game_manager_, "instruction_window", 51);
	pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pause_instruction_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pauseButtons_[0] = new Revolution(game_manager_, "pose_return_game");
	pauseButtons_[1] = new Revolution(game_manager_, "pose_restart");
	pauseButtons_[2] = new Revolution(game_manager_, "pose_select");
	pauseButtons_[3] = new Revolution(game_manager_, "pose_instruction");
	pauseButtons_[4] = new Revolution(game_manager_, "pose_option");
	pauseButtons_[0]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[0]->GetTransformComponent()->SetPosition(0.0f, 365.0f);
	pauseButtons_[1]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[1]->GetTransformComponent()->SetPosition(0.0f, 200.0f);
	pauseButtons_[2]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[2]->GetTransformComponent()->SetPosition(0.0f, 35.0f);
	pauseButtons_[3]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[3]->GetTransformComponent()->SetPosition(0.0f, -130.0f);
	pauseButtons_[4]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[4]->GetTransformComponent()->SetPosition(0.0f, -295.0f);
	for(auto& it : pauseButtons_)
		it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
}

SceneBase::~SceneBase()
{
	std::cout << std::format("[{}] -> Destructor\n", scene_name_);
}

void SceneBase::PauseWindow()
{
	// ここで操作を記述
	auto& input = InputManager::GetInstance();
	// ウィンドウが更に開いていないときだけボタン操作を実行
	if (!isWindowOpen)
	{
		if (input.GetKeyTrigger(VK_UP))				// 上下移動
			pause_select_button_--;
		if (input.GetKeyTrigger(VK_DOWN))
			pause_select_button_++;
		if (pause_select_button_ > 4)				// 折り返し処理
			pause_select_button_ = 0;
		if (pause_select_button_ < 0)
			pause_select_button_ = 4;
	}
	else
	{
		if (input.GetKeyTrigger(VK_X))
		{
			if (pause_select_button_ == 3) 
			{
				isWindowOpen = false;
				pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			if (pause_select_button_ == 4)
			{
				isWindowOpen = false;
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
	if (input.GetKeyTrigger(VK_RETURN))
	{
		switch (pause_select_button_)
		{
		case 0:	// ゲーム画面に戻る
			stageState_ = StageState::Game;
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Active);	// 稼働コンテナのオブジェクトを全てポーズ状態に
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
			game_manager_->ChangeScene(SceneName::Title);
			break;
		case 3:	// 操作説明を表示
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			isWindowOpen = true;
			break;
		case 4:	// オプションウィンドウを表示
			OptionWindow();
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
	// ギアのMAX個数によってUVを変更
	switch (gearMaxCount_)
	{
	case 1:
	{
		gearSpriteComponent->SetUV({ 1.0f, 0.0f });
	}
		break;
	case 2:
	{
		gearSpriteComponent->SetUV({ 2.0f, 0.0f });
	}
		break;
	case 3:
	{
		gearSpriteComponent->SetUV({ 3.0f, 0.0f });
	}
		break;
	case 4:
	{
		gearSpriteComponent->SetUV({ 4.0f, 0.0f });
	}
		break;
	case 5:
	{
		gearSpriteComponent->SetUV({ 5.0f, 0.0f });
	}
		break;
	default:
		break;
	}
	// ギアの取得状態によってUVを変更
	switch (game_manager_->GetItemCount())
	{
	case 0:
	{
		gearGetSpriteComponent->SetUV({ 0.0f, 0.0f });
	}
	break;
	case 1:
	{
		gearGetSpriteComponent->SetUV({ 1.0f, 0.0f });
	}
	break;
	case 2:
	{
		gearGetSpriteComponent->SetUV({ 2.0f, 0.0f });
	}
	break;
	case 3:
	{
		gearGetSpriteComponent->SetUV({ 3.0f, 0.0f });
	}
	break;
	case 4:
	{
		gearGetSpriteComponent->SetUV({ 4.0f, 0.0f });
	}
	break;
	case 5:
	{
		gearGetSpriteComponent->SetUV({ 5.0f, 0.0f });
	}
	break;
	default:
		break;
	}

}

