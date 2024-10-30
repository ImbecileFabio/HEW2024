//=================================================================
// [GameManager.cpp] ゲームマネージャーモジュール 
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：ゲームの状態とオブジェクトの管理、追加と削除、入力、更新、描画など
//=================================================================

/*----- インクルード -----*/
#include "StdAfx.h"
#include "GameManager.h"
#include "Renderer.h"
#include "GameObjects/GameObject.h"



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
	renderer_ = new Renderer(this);

	game_objects_.clear();
	pending_game_objects_.clear();
	renderer_->Init();

	std::cout << "[ゲームマネージャー] -> ゲームオブジェクト生成開始\n";
	std::cout << "\n";

	// player_ = new Player(this);

	std::cout << "\n";
	std::cout << "[ゲームマネージャー] -> ゲームオブジェクト生成終了\n";
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << "[ゲームマネージャー] -> 終了処理\n";

	renderer_->Uninit();



	std::cout << "[ゲームマネージャー] -> セーブデータのアンロード\n";
	std::cout << "[ゲームマネージャー] -> グラフィックスの破棄\n";
}

//-----------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	std::cout << "[ゲームマネージャ] -> 更新処理\n";
	// ゲームオブジェクトの更新
	this->UpdateGameObjects();
}

//-----------------------------------------------------------------
// 出力生成処理
//-----------------------------------------------------------------
void GameManager::GenerateOutputAll(void)
{
	std::cout << "[ゲームマネージャ] -> 出力生成処理\n";
	// 初期色に
	renderer_->Begin();

	renderer_->Draw();

	// 描画終了
	renderer_->End();
}

//-----------------------------------------------------------------
// ゲームオブジェクトの追加処理
//-----------------------------------------------------------------
void GameManager::AddGameObject(GameObject* gameObject)
{
	// ゲームオブジェクトのお更新中かで登録先を変更
	if (updating_game_objects_)
		pending_game_objects_.emplace_back(gameObject);	// 待機コンテナ
	else
		game_objects_.emplace_back(gameObject);			// 稼働コンテナ
}

//-----------------------------------------------------------------
// ゲームオブジェクトの削除処理
//-----------------------------------------------------------------
void GameManager::RemoveGameObject(GameObject* gameObject)
{
	// 待機コンテナ
	// "gameObject"をコンテナの中から探し出して破棄
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), gameObject);
	if (iter != game_objects_.end())
	{
		// 一致する"gameObject"をコンテナの末尾へ移動させ、メモリ自体を破棄する
		std::iter_swap(iter, game_objects_.end() - 1);
		game_objects_.pop_back();
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
		game_object->Update();
	updating_game_objects_ = false;

	// 待機リストのゲームオブジェクトの操作
	for (auto pending_game_object : pending_game_objects_)
	{
		pending_game_object->Update();
		game_objects_.emplace_back(pending_game_object);
	}

}


//=================================================================
//			End of File 
//=================================================================
