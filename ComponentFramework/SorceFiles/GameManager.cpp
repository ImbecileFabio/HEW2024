//=================================================================
// [GameManager.cpp] ゲームマネージャーモジュール 
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態とオブジェクトの管理、追加と削除、入力、更新、描画など
//=================================================================

/*----- インクルード -----*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "GameManager.h"
#include "Renderer.h"
#include "ImGuiManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/GameObject/Player.h"
#include "GameObjects/GameObject/Camera.h"


//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	std::cout << "[ゲームマネージャー] -> 起動\n";
	this->InitAll();

}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	this->UninitAll();
	std::cout << "[ゲームマネージャー] -> 停止\n";
}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << "[ゲームマネージャー] -> 初期化処理\n";

	// レンダラー初期化
	renderer_ = std::make_shared<Renderer>();
	renderer_->Init();

	game_objects_.clear();
	pending_game_objects_.clear();


	// ゲームオブジェクト初期化
	player_ = std::make_shared<Player>(this);
	//camera_ = std::make_shared<Camera>(this);
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << "[ゲームマネージャー] -> リソース開放開始\n";

	if (renderer_)
	{
		renderer_->Uninit();
		renderer_.reset();
	}


	std::cout << "[ゲームマネージャー] -> リソース開放終了\n";



	std::cout << "[ゲームマネージャー] -> セーブデータのアンロード\n";
	std::cout << "[ゲームマネージャー] -> グラフィックスの破棄\n";
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// ゲームオブジェクトの更新
	this->UpdateGameObjects();
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
// ゲームオブジェクトの追加処理
//-----------------------------------------------------------------
void GameManager::AddGameObject(GameObject* gameObject)
{
	// ゲームオブジェクトの更新中かで登録先を変更
	if (updating_game_objects_)
		pending_game_objects_.emplace_back(gameObject);	// 待機コンテナ
	else
        game_objects_.emplace_back(gameObject);			// 稼働コンテナ
        }

//-----------------------------------------------------------------
// ゲームオブジェクトの削除処理
//-----------------------------------------------------------------
/*
* @param	削除するゲームオブジェクト
* @brief	コンテナの中から削除するオブジェクトを探して削除する
*/
void GameManager::RemoveGameObject(GameObject* gameObject) {
	// 待機コンテナ
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), gameObject);
	if (iter != pending_game_objects_.end())
	{
		std::iter_swap(iter, pending_game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		pending_game_objects_.pop_back();						// 待機コンテナから削除

	}

	// 稼働コンテナ
	iter = std::find(game_objects_.begin(), game_objects_.end(), gameObject);
	if (iter != game_objects_.end())
	{
		std::iter_swap(iter,game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		game_objects_.pop_back();						// 稼働コンテナから削除

	}

}
//-----------------------------------------------------------------
// ゲームオブジェクトの総更新処理
//-----------------------------------------------------------------
/*-----  ゲームオブジェクト -----*/
void GameManager::UpdateGameObjects(void)
{
	// すべてのゲームオブジェクトの更新
	updating_game_objects_ = true;
	for (auto game_object : game_objects_)
		game_object->Update();		// 更新処理
	updating_game_objects_ = false;

	// 待機リストのゲームオブジェクトの操作
	for (auto pending_game_object : pending_game_objects_)
	{
		pending_game_object->Update();
		game_objects_.emplace_back(pending_game_object);
	}
	pending_game_objects_.clear();

	// ゲームオブジェクトが破棄状態かチェック
	std::vector<class GameObject*> dead_game_objects;
	for (auto game_object : game_objects_)
	{
		if (game_object->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(game_object);
		}
	}

}


//=================================================================
//			End of File 
//=================================================================
