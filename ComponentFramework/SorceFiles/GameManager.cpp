//=================================================================
// [GameManager.cpp] ゲームマネージャーモジュール 
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態とオブジェクトの管理、追加と削除、入力、更新、描画など
//=================================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>

#include "GameManager.h"
#include "ColliderManager.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "ImGuiManager.h"


//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	std::cout << std::format("[GameManager] -> Constructor\n");
	// レンダラー初期化
	renderer_ = new Renderer();
	renderer_->Init();

	// オーディオマネージャー初期化
	//audio_manager_ = new AudioManager();

	// コライダーマネージャー初期化
		
	collider_manager_ = ColliderManager::Create();

	this->InitAll();

}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	// 解放処理
	std::cout << std::format("[GameManager] -> Destructor\n");
	this->UninitAll();

	delete current_scene_;
	delete renderer_;
	delete audio_manager_;
	delete collider_manager_;

}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << std::format("[GameManager] -> InitAll Start\n");



	// オブジェクトリストの初期化
	game_objects_.clear();
	pending_game_objects_.clear();

	// シーンの初期化
	current_scene_ = new TitleScene(this);
    // ゲームオブジェクト初期化
	current_scene_->Init();
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << std::format("[GameManager] -> UninitAll Start\n");

	// ゲームオブジェクトの破棄
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// ゲームオブジェクトの更新
	this->UpdateGameObjects();
	this->collider_manager_->UpdateAll();
	ImGuiManager::staticPointer->ImGuiShowWindow(this->game_objects_);

	this->current_scene_->Update();

}
//-----------------------------------------------------------------
// 出力生成処理
//-----------------------------------------------------------------
void GameManager::GenerateOutputAll(void)
{
	if(renderer_)
	{

		renderer_->Begin();
		renderer_->Draw();
		

		ImGuiManager::staticPointer->ImGuiRender();	// ImGuiのウィンドウを描画

		renderer_->End();

	}
}

//-----------------------------------------------------------------
// シーン切り替え処理
//-----------------------------------------------------------------
void GameManager::ChangeScene(SceneName _scene)
{
	std::cout << std::format("\n[GameManager] -> ChangeScene\n");

	// 現在のシーンの終了処理
	if (current_scene_ != nullptr)
	{
		delete current_scene_;
		current_scene_ = nullptr;
	}

	switch (_scene)
	{
	case Title:
		current_scene_ = new TitleScene(this);
		break;
	case Stage1_1:
		current_scene_ = new Stage1_1Scene(this);
		break;
	case Result:
		current_scene_ = new ResultScene(this);
		break;
	default:
		std::cout << std::format("[GameManager] -> ChangeScene Error\n");
		break;
	}
}

//-----------------------------------------------------------------
// ゲームオブジェクトの追加処理
//-----------------------------------------------------------------
void GameManager::AddGameObject (GameObject* gameObject)
{
	// ゲームオブジェクトの更新中かで登録先を変更
	if (updating_game_objects_)
	{
		pending_game_objects_.emplace_back(gameObject);	// 待機コンテナ
	}
	else
	{
		game_objects_.emplace_back(gameObject);			// 稼働コンテナ
	}
}

//-----------------------------------------------------------------
// @param	削除するゲームオブジェクト
// @brief	コンテナの中から削除するオブジェクトを探して削除する
//-----------------------------------------------------------------
void GameManager::RemoveGameObject(GameObject* _gameObject) {
	// 待機コンテナ
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), _gameObject);
	if (iter != pending_game_objects_.end())
	{
		std::iter_swap(iter, pending_game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		pending_game_objects_.pop_back();						// 待機コンテナから削除

	}

	// 稼働コンテナ
	iter = std::find(game_objects_.begin(), game_objects_.end(), _gameObject);
	if (iter != game_objects_.end())
	{
		std::iter_swap(iter,game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		game_objects_.pop_back();						// 稼働コンテナから削除
	}

}
//-----------------------------------------------------------------
// ゲームオブジェクトの総更新処理
//-----------------------------------------------------------------
void GameManager::UpdateGameObjects(void)
{
	// すべてのゲームオブジェクトの更新
	updating_game_objects_ = true;

	for (auto& gameObject : game_objects_)
	{
		gameObject->Update();		// 更新処理
	}
	updating_game_objects_ = false;

	// 待機リストのゲームオブジェクトの操作
	for (auto& pendingGameObject : pending_game_objects_)
	{
		pendingGameObject->Update();
		game_objects_.emplace_back(pendingGameObject);
	}
	pending_game_objects_.clear();

	// ゲームオブジェクトが破棄状態かチェック
	std::vector<GameObject*> dead_game_objects;
	for (auto& gameObject : game_objects_)
	{
		if (gameObject->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(gameObject);
		}
	}
}