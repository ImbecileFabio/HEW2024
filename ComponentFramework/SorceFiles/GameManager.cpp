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
#include "ImGuiManager.h"
#include "PemdulumManager.h"
#include "TextureManager.h"
#include "FadeManager.h"

#include "Renderer.h"

#include "GameObjects/GameObject.h"

//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	// レンダラー初期化
	renderer_ = new Renderer();
	renderer_->Init();

	// テクスチャのロード
	TextureManager::GetInstance().Init();

	// フェードマネージャ初期化
	fade_manager_ = new FadeManager(this);

	// コライダーマネージャー初期化
	collider_manager_ = ColliderManager::Create();
	
	// 振り子マネージャー初期化
	pendulum_manager_ = PendulumManager::GetInstance();
	pendulum_manager_->SetGM(this);
	this->InitAll();
}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	// 解放処理
	this->UninitAll();

	delete current_scene_;
	delete renderer_;
	delete collider_manager_;
	delete pendulum_manager_;
	delete fade_manager_;
}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
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
	// ゲームオブジェクトの破棄
	this->ClearAllObjects();
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll(float _deltaTime)
{
	// フェードマネージャの更新
	fade_manager_->Update(_deltaTime);

	// ゲームオブジェクトの更新
	this->current_scene_->Update();
	this->UpdateGameObjects(_deltaTime);
	this->collider_manager_->UpdateAll();
	this->pendulum_manager_->Update();
	ImGuiManager::staticPointer->ImGuiShowWindow();
}

//-----------------------------------------------------------------
// 出力生成処理
//-----------------------------------------------------------------
void GameManager::GenerateOutputAll(void)
{
	if (renderer_)
	{

		renderer_->Begin();
		renderer_->Draw();

		fade_manager_->Draw();

		ImGuiManager::staticPointer->ImGuiRender();

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
		delete obj;
	}

	// ゲームオブジェクトリストをクリア
	game_objects_.clear();
}

//-----------------------------------------------------------------
// @param 次のシーン名
// @breaf シーン切り替える時にフェードイン・アウトを行う
//			フェードアウトが終わるとchangesceneを呼び出す
//-----------------------------------------------------------------
void GameManager::TransitionToScene(SceneName _nextScene)
{
	if (fade_manager_->GetIsPlaying()) {
		return; // フェード中なら二重実行を防ぐ
	}

	// フェードアウト開始
	fade_manager_->StartFadeOut("fade_out", [this, _nextScene]() {

		// フェードアウト終了時にシーンを切り替え
		ChangeScene(_nextScene);


		// シーン変更後にフェードインを開始
		fade_manager_->StartFadeIn("fade_in");

		});
}

//-----------------------------------------------------------------
// @param 次のシーン名
// @breaf シーン切り替え処理
//-----------------------------------------------------------------
void GameManager::ChangeScene(SceneName _nextScene) 
{



// 前のシーン名を保存しておく
	std::string old_scene_name = current_scene_->GetSceneName();
	// 前のシーンのギア獲得数を保存
	int gearMaxCount = current_scene_->GetGearMaxCount();
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
		switch (_nextScene) {
		case Title:
			current_scene_ = new TitleScene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_1:
			current_scene_ = new Stage1_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_2:
			current_scene_ = new Stage1_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_3:
			current_scene_ = new Stage1_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_4:
			current_scene_ = new Stage1_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_1:
			current_scene_ = new Stage2_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_2:
			current_scene_ = new Stage2_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_3:
			current_scene_ = new Stage2_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_4:
			current_scene_ = new Stage2_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_1:
			current_scene_ = new Stage3_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_2:
			current_scene_ = new Stage3_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_3:
			current_scene_ = new Stage3_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_4:
			current_scene_ = new Stage3_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Result:
		{
			itemCount = 0;
			current_scene_ = new ResultScene(this);
			auto result = dynamic_cast<ResultScene*>(current_scene_);
			result->SetGearMaxNum(gearMaxCount);
			current_scene_->SetOldSceneName(old_scene_name);
			current_scene_->Init();
		}
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
void GameManager::UpdateGameObjects(float _deltaTime)
{
	// すべてのゲームオブジェクトの更新
	updating_game_objects_ = true;
	for (auto& gameObject : game_objects_)
	{
		gameObject->SetDeltaTime(_deltaTime);	// デルタタイムの設定
		gameObject->Update();		// 更新処理
	}
	updating_game_objects_ = false;

	// 待機リストのゲームオブジェクトの操作
	for (auto& pendingGameObject : pending_game_objects_)
	{
		pendingGameObject->SetDeltaTime(_deltaTime);
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