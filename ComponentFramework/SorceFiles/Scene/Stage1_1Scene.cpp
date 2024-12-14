//==================================================
// [Stage1_1Scene.cpp] ステージ1-1シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-1を管理をするクラス
//==================================================

/*----- インクルード -----*/
#include "Stage1_1Scene.h"

#include "../GameManager.h"
#include "../ColliderManager.h"
#include "../GameObjects/Component/ColliderComponent/ColliderBaseComponent.h"
#include "../GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/BackGround.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Pendulum.h"
#include "../GameObjects/GameObject/Tile.h"
#include "../GameObjects/GameObject/Robot.h"
#include "../GameObjects/GameObject/Lift.h"
#include "../GameObjects/GameObject/Item.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Stage1_1Scene::Stage1_1Scene(GameManager* _gameManager)
	: SceneBase(_gameManager, "Stage1_1")
{
	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Stage1_1Scene::~Stage1_1Scene()
{
	this->Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Stage1_1Scene::Init()
{
	camera_ = new Camera(game_manager_);
	back_ground_ = new BackGround(game_manager_);
	tile_ = new Tile(game_manager_);

	robot_ = new Robot(game_manager_);
	
	lift_ = new Lift(Lift::MoveState::side, { 100.0f, 0.0f, 0.0f }, {-100.0f, 0.0f, 0.0f}, game_manager_);
	items_.resize(2, nullptr);  // 配列を2つ分確保

	items_[0] = new Item(game_manager_);
	items_[0]->GetComponent<TransformComponent>()->SetPosition({ 0.0f, 0.0f, 0.0f });
	items_[0]->GetComponent<TransformComponent>()->SetScale({ 100.0f, 100.0f, 0.0f });

	auto f = std::function<void(GameObject*)>(std::bind(&Item::OnCollisionEnter, items_[0], std::placeholders::_1));
	items_[0]->GetComponent<ColliderEventComponent>()->AddEvent(0, f);

	items_[1] = new Item(game_manager_);
	items_[1]->GetComponent<TransformComponent>()->SetPosition({ 140.0f, 0.0f, 0.0f });
	items_[1]->GetComponent<TransformComponent>()->SetScale({ 100.0f, 100.0f, 0.0f });

	auto f2 = std::function<void(GameObject*)>(std::bind(&Item::OnCollisionEnter, items_[1], std::placeholders::_1));
	items_[1]->GetComponent<ColliderEventComponent>()->AddEvent(1, f2);
	//pendulum_ = new Pendulum(game_manager_);
	
	// GameManegerで生成して、ColliderManagerに登録する
	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{	// あたり判定のあるオブジェクトをコライダーマネージャーに登録
		if (colliderObjects->GetComponent<ColliderBaseComponent>())
		{
			game_manager_->GetColliderManager()->AddGameObject(colliderObjects);
		}
	}

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void Stage1_1Scene::Uninit()
{
	delete camera_;

	delete back_ground_;
	delete pendulum_;
	delete tile_;
	delete robot_;
	delete lift_;
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Stage1_1Scene::Update()
{

}
