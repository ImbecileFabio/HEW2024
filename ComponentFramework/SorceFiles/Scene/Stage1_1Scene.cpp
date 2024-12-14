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

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/BackGround.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Pendulum.h"
#include "../GameObjects/GameObject/Tile.h"
#include "../GameObjects/GameObject/Robot.h"
#include "../GameObjects/GameObject/Lift.h"

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
	//back_ground_ = new BackGround(game_manager_);
	//tile_ = new Tile(game_manager_);

	robot_ = new Robot(game_manager_);
	
	lift_ = new Lift(Lift::MoveState::side, { 100.0f, 0.0f, 0.0f }, {-100.0f, 0.0f, 0.0f}, game_manager_);
	//pendulum_ = new Pendulum(game_manager_);

	State = Game;
	
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

	if (InputManager::GetInstance().GetKeyTrigger(VK_R))
	{
		game_manager_->ChangeScene(SceneName::Title);
	}

}

// コパイロット君が出力したコメント
// �Q�[���I�u�W�F�N�g�̒ǉ�
