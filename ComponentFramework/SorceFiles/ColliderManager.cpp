//=================================================================
// [ColliderManager.cpp] コライダーマネージャーモジュール 
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：コライダーの管理を行う
//=================================================================
/*----- インクルード -----*/
#include "ColliderManager.h"
#include "GameObjects/GameObject/ColliderTestObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
//-----------------------------------------------------------------
// @brief  コンストラクタ
//-----------------------------------------------------------------
ColliderManager::ColliderManager(void)
	:updating_game_objects_(false)
{
	this->InitAll();	// 初期化
}
//-----------------------------------------------------------------
// @brief  デストラクタ
//-----------------------------------------------------------------
ColliderManager::~ColliderManager(void)
{
}
//-----------------------------------------------------------------
// @brief  初期化処理
//-----------------------------------------------------------------
void ColliderManager::InitAll(void)
{
	collider_game_objects_.clear();	// 当たり判定用コンテナのクリア
}
//-----------------------------------------------------------------
// @brief  更新処理
//-----------------------------------------------------------------
void ColliderManager::UpdateAll(void)
{
	this->UpdateGameObjects();
}
//-----------------------------------------------------------------
// @brief  終了処理
//-----------------------------------------------------------------
void ColliderManager::UninitAll(void)
{
}
//-----------------------------------------------------------------
// @brief  オブジェクトを追加
// @param  _gameObject 追加するゲームオブジェクト
//-----------------------------------------------------------------
void ColliderManager::AddGameObject(GameObject* _gameObject)
{
	// ゲームオブジェクトの更新中かで登録先を変更
	if (updating_game_objects_)
	{
		collider_game_objects_.emplace_back(_gameObject);	// 待機コンテナ
	}
	else
	{
		collider_game_objects_.emplace_back(_gameObject);			// 稼働コンテナ
	}
}
//-----------------------------------------------------------------
// @brief  オブジェクトを削除
// @param  _gameObject 削除するゲームオブジェクト
//-----------------------------------------------------------------
void ColliderManager::RemoveGameObject(GameObject* _gameObject)
{
	// 待機コンテナ
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), _gameObject);
	if (iter != pending_game_objects_.end())
	{
		std::iter_swap(iter, pending_game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		pending_game_objects_.pop_back();						// 待機コンテナから削除

	}
	// 稼働コンテナ
	iter = std::find(collider_game_objects_.begin(), collider_game_objects_.end(), _gameObject);
	if (iter != collider_game_objects_.end())
	{
		std::iter_swap(iter, collider_game_objects_.end() - 1);	// コンテナの最後尾と入れ替え
		collider_game_objects_.pop_back();						// 稼働コンテナから削除
	}
}
//-----------------------------------------------------------------
// @brief  オブジェクトのUpdateをすべて呼びだす処理
//-----------------------------------------------------------------
void ColliderManager::UpdateGameObjects(void)
{
	// すべてのゲームオブジェクトの更新
	updating_game_objects_ = true;
	//collider_game_objects_.clear();	// Clearしないと処理が落ちる
	for (auto& gameObject : collider_game_objects_)
	{
		gameObject->Update();		// 更新処理
	}
	// 当たり判定の処理
	for (int i = 0; i < collider_game_objects_.size(); i++)
	{
		for (int j = i + 1; j < collider_game_objects_.size(); j++)
		{	// 衝突したか、していないか
			if (collider_game_objects_[i]->GetComponent<ColliderBaseComponent>()->
				CheckCollisionCollider(collider_game_objects_[j]->GetComponent<ColliderBaseComponent>()))
			{	
				// 当たった側の処理を呼びだす
				std::cout << std::format("あいうえお\n");
				collider_game_objects_[i]->OnCollisionEnter2D(*collider_game_objects_[j]);
			}
		}
	}
	updating_game_objects_ = false;

	// 待機リストのゲームオブジェクトの操作
	for (auto& pendingGameObject : pending_game_objects_)
	{
		pendingGameObject->Update();
		collider_game_objects_.emplace_back(pendingGameObject);
	}
	pending_game_objects_.clear();

	// ゲームオブジェクトが破棄状態かチェック
	std::vector<GameObject*> dead_game_objects;
	for (auto& gameObject : collider_game_objects_)
	{
		if (gameObject->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(gameObject);
		}
	}
}