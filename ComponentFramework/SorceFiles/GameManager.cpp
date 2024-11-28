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
#include "Renderer.h"
#include "ImGuiManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/GameObject/Player.h"
#include "GameObjects/GameObject/Camera.h"
#include "GameObjects/GameObject/Pendulum.h"

// デバッグようおぶじぇえくと
#include "GameObjects/GameObject/TestObject.h"
#include "GameObjects/GameObject/ColliderTestObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"

//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	std::cout << std::format("[GameManager] -> Constructor\n");
	this->InitAll();

}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	this->UninitAll();
	std::cout << std::format("[GameManager] -> Destructor\n");
}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << std::format("[GameManager] -> InitAll Start\n");

	// レンダラー初期化
	renderer_ = new Renderer();
	renderer_->Init();

	game_objects_.clear();
	pending_game_objects_.clear();


    // ゲームオブジェクト初期化
	camera_ = new Camera(this);
    //player_ = new Player(this);
	test_object_ = new TestObject(this);
	//pendulum_ = new Pendulum(this);
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << std::format("[GameManager] -> UninitAll Start\n");

	// ゲームオブジェクトの破棄
	delete renderer_;
	delete camera_;
	delete player_;

	delete test_object_;
	//delete pendulum_;
	

	//std::cout << std::format("[GameManager] -> セーブデータのアンロード\n");
	//std::cout << std::format("[GameManager] -> グラフィックスの破棄\n");
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// ゲームオブジェクトの更新
	this->UpdateGameObjects();
	ImGuiManager::staticPointer->ImGuiShowWindow(this->game_objects_);
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
// ゲームオブジェクトの削除処理
//-----------------------------------------------------------------
/*
* @param	削除するゲームオブジェクト
* @brief	コンテナの中から削除するオブジェクトを探して削除する
*/
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
	collider_game_objects_.clear();	// Clearしないと処理が落ちる

	for (auto& gameObject : game_objects_)
	{
		gameObject->Update();		// 更新処理
		if (gameObject->GetComponent<CircleColliderComponent>())
		{
			collider_game_objects_.emplace_back(gameObject);
		}
	}
	// 当たり判定コンテナで処理
	for (int i = 0; i < collider_game_objects_.size(); i++)
	{
		for (int j = i + 1; j < collider_game_objects_.size(); j++)
		{
			collider_game_objects_[i]->GetComponent<CircleColliderComponent>()->
				CheckCollisionCollider(collider_game_objects_[j]->GetComponent<CircleColliderComponent>());
		}
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