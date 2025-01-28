//=================================================================
// [ColliderManager.cpp] コライダーマネージャーモジュール 
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：コライダーの管理を行う
//=================================================================
/*----- インクルード -----*/
#include "ColliderManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/BoxColliderComponent.h"
#include "GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "GameObjects/Component/RobotMoveComponent.h"
#include "GameObjects/Component/RigidbodyComponent/VelocityComponent.h"
#include "ImGuiManager.h"
//----------------------------------------------------------------
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
	collider_out_objects_.clear();
	pending_game_objects_.clear();

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
	collider_game_objects_.clear();	// 当たり判定用コンテナのクリア
	collider_out_objects_.clear();
	pending_game_objects_.clear();
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
		collider_game_objects_.emplace_back(_gameObject);	// 稼働コンテナ
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
	for (auto it1 = collider_game_objects_.begin(); it1 != collider_game_objects_.end(); ++it1) 
	{
		auto collider1 = (*it1)->GetComponent<ColliderBaseComponent>();
		auto event1 = (*it1)->GetComponent<EventBaseComponent>();

		// collider1 または event1 が nullptr の場合はスキップ
		if (collider1 == nullptr || event1 == nullptr) continue;

		for (auto it2 = collider_game_objects_.begin(); it2 != collider_game_objects_.end(); ++it2)
		{
			// 自己判定をスキップ
			if (it1 == it2) continue;

			auto collider2 = (*it2)->GetComponent<ColliderBaseComponent>();
			if (collider2 == nullptr) continue;

			// 衝突判定
			if (collider1->CheckCollisionCollider(collider2))
			{
				// イベント処理
				size_t id = event1->GetId();
				event1->AllUpdate(*it2, id);
			}
			else
			{
			}
		}
	}
	updating_game_objects_ = false;
	// 当たり判定を取らなくなったオブジェクトの移動
	for (auto it = collider_game_objects_.begin(); it != collider_game_objects_.end(); ) 
	{

		//if ((*it)->GetState() == GameObject::State::Paused)
		//{
		//	collider_out_objects_.emplace_back(std::move(*it));
		//	it = collider_game_objects_.erase(it); // 要素を削除しつつ次の要素へ
		//}
		//else 
		//{
		//	++it;
		//}
		if ((*it)->GetState() == GameObject::State::Dead)
		{
			collider_out_objects_.emplace_back(std::move(*it));
			it = collider_game_objects_.erase(it); // 要素を削除しつつ次の要素へ
		}
		else 
		{
			++it;
		}
	}
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


//#include <functional>
//
//int TestFunc() {
//	return 100;
//}
//
//class FuncClass {
//public:
//	int operator+ (int a) {
//		return a * rate;
//	}
//	void operator() (int i) {
//
//	}
//	int rate;
//};
//
//class MyVector {
//public:
//	MyVector();
//	MyVector(float x, float y, float z) {
//		this->x = x:
//		this->x = x :
//			this->x = x :
//	}
//	MyVector(XMFLOAT3 src) {
//		MyVector(src.x, src.y, src.z);
//	}
//
//	static MyVector operator+(MyVector left, MyVector right) {
//		MyVector result;
//		result.x = -100.0f:
//		exit();
//		new int[100];
//		result.x = left.x + right.x;
//		result.y = left.y + right.y;
//		result.z = left.z + right.z;
//		return result;
//	}
//	float x, y, z;
//
//
//
//};
//FuncClass funcInst;
//funcInst.operator()(100);
//funcInst(100);
//
//int ret = funcInst.operator+(10);
//ret = funcInst + 10;
//
//
//std::list<std::function<int>> funcs;
//
//funcs.push_back(funcInst);
//
//funcs.push_back(TestFunc);
//for (int idx = 0; idx < func.size(); idx++) {
//	funcs[idx]();
//}