//=================================================================
// [GameManager.cpp] ゲームマネージャーモジュール 
// 著者：Keita Arima
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
#include "PemdulumManager.h"


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

	// 振り子マネージャー初期化
	pendulum_manager_ = PendulumManager::GetInstance();

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

	ImGuiManager::staticPointer->SetObjectList(game_objects_);
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << std::format("[GameManager] -> UninitAll Start\n");

	// ゲームオブジェクトの破棄
	this->ClearAllObjects();
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// ゲームオブジェクトの更新
	this->current_scene_->Update();
	this->UpdateGameObjects();
	this->collider_manager_->UpdateAll();
	this->pendulum_manager_->Update();
	ImGuiManager::staticPointer->ImGuiShowWindow();
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
// @biref オブジェクトをすべてクリア
//	一度deadgameobjectsに移動させてから消去することでイテレータがバグるのを防いでます
// （gameobjectはデストラクタでgameobjectsから勝手に出ていくのでずれる）
//-----------------------------------------------------------------
void GameManager::ClearAllObjects(void)
{
	std::cout << "クリアオールオブジェクト\n";

	// 振り子マネージャとコライダーマネージャの初期化
	pendulum_manager_->Uninit();
	collider_manager_->UninitAll();

	// 削除対象リストを作成
	std::vector<GameObject*> dead_game_objects;

	// 稼働中のゲームオブジェクトを削除対象リストに追加
	for (auto& obj : game_objects_) {
		dead_game_objects.push_back(obj);
	}
	// 待機中のゲームオブジェクトを削除対象リストに追加
	for (auto& obj : pending_game_objects_){
		dead_game_objects.push_back(obj);
	}

	// 削除対象リスト内のオブジェクトを安全に削除
	for (auto& obj : dead_game_objects) {
		std::cout << std::format("\n[{}] -> delete\n", obj->GetObjectName());
		delete obj;
	}

	// ゲームオブジェクトリストをクリア
	game_objects_.clear();
}


//-----------------------------------------------------------------
// シーン切り替え処理
//-----------------------------------------------------------------
void GameManager::ChangeScene(SceneName _scene) {
	std::cout << "\n[GameManager] -> ChangeScene\n";

	// 現在のシーンの終了処理
	if (current_scene_) {
		try {
			current_scene_->Uninit();
			delete current_scene_;
		}
		catch (const std::exception& e) {
			std::cerr << "[ChangeScene] -> 例外 : " << e.what() << std::endl;
		}
		current_scene_ = nullptr;
	}

	// ゲームオブジェクトの全削除
	try {
		ClearAllObjects();
	}
	catch (const std::exception& e) {
		std::cerr << "[ClearAllObjects] -> 例外 : " << e.what() << std::endl;
	}

	// 新しいシーンの初期化
	try {
		switch (_scene) {
		case Title:
			current_scene_ = new TitleScene(this);
			break;
		case Stage1_1:
			current_scene_ = new Stage1_1Scene(this);
			break;
		case Result:
			itemCount = 0;
			current_scene_ = new ResultScene(this);
			break;
		default:
			std::cout << std::format("[GameManager] -> ChangeScene Error\n");
			break;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[ChangeScene] -> 例外 : " << e.what() << std::endl;
	}

	ImGuiManager::staticPointer->ResetSelectObject();
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