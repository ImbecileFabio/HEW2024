#include "Stage2_3Scene.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../../PemdulumManager.h"
#include "../../InputManager.h"
#include "../../TileMapManager.h"
#include "../../AudioManager.h"

#include "../../GameObjects/GameObject/BackGround.h"
#include "../../GameObjects/GameObject/Camera.h"
#include "../../GameObjects/GameObject/Pendulum.h"
#include "../../GameObjects/GameObject/Tile.h"
#include "../../GameObjects/GameObject/Robot.h"
#include "../../GameObjects/GameObject/Lift.h"
#include "../../GameObjects/GameObject/Item.h"
#include "../../GameObjects/GameObject/Revolution.h"
#include "../../GameObjects/GameObject/HammerCursor.h"

#include "../../GameObjects/Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "../../GameObjects/Component/PendulumMovementComponent.h"
#include "../../GameObjects/Component/ChildrenComponent.h"


constexpr int gearCounter_2_3 = 2;		// ギアの獲得数
constexpr int hammerCounter_2_3 = 3;	// 叩ける上限
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Stage2_3Scene::Stage2_3Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage2_3")
{
	Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Stage2_3Scene::~Stage2_3Scene()
{
	Uninit();
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Stage2_3Scene::Init()
{
	auto mapData = tile_map_manager_->LoadCSV("MapData/Stage2/Stage2_3.csv");
	tile_map_manager_->LoadTileMap(mapData);

	camera_ = new Camera(game_manager_);
	back_ground_ = new BackGround(game_manager_);
	hammerCursor_ = new HammerCursor(game_manager_);

	gearMaxCount_ = gearCounter_2_3;	// 定数を代入
	hammerMaxCount_ = hammerCounter_2_3;

	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);

	stageState_ = Game;

	// GameManagerで生成して、ColliderManagerに登録する
	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{	// 子オブジェクトを追加
		auto childrenComponent = colliderObjects->GetComponent<ChildrenComponent>();
		if (childrenComponent)
		{
			auto& childrenObjects = childrenComponent->GetChildren();
			for (auto& children : childrenObjects)
			{
				// あたり判定のあるオブジェクトをコライダーマネージャーに登録
				if (children->GetComponent<ColliderBaseComponent>())
				{
					game_manager_->GetColliderManager()->AddGameObject(children);
				}
			}
		}
		// あたり判定のあるオブジェクトをコライダーマネージャーに登録
		if (colliderObjects->GetComponent<ColliderBaseComponent>())
		{
			game_manager_->GetColliderManager()->AddGameObject(colliderObjects);
		}
	}

	game_manager_->GetPendulumManager()->SetHammerCursor(hammerCursor_);

	for (auto& pendulumObject : game_manager_->GetGameObjects()) {
		auto childrenComponent = pendulumObject->GetComponent<ChildrenComponent>();
		if (childrenComponent)
		{
			auto& childrenObjects = childrenComponent->GetChildren();
			for (auto& children : childrenObjects)
			{
				// ペンデュラムオブジェクトをコライダーマネージャーに登録
				if (children->GetComponent<PendulumMovementComponent>())
				{
					game_manager_->GetPendulumManager()->AddGameObject(children);
				}
			}
		}
		if (pendulumObject->GetComponent<PendulumMovementComponent>()) {
			game_manager_->GetPendulumManager()->AddGameObject(pendulumObject);
		}
	}

	PendulumManager::GetInstance()->SetSelectedPendulum(PendulumManager::GetInstance()->GetPendulumList().front());
	AudioManager::GetInstance()->Play(SoundLabel_StageBGM);


}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Stage2_3Scene::Update()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_R))
		stageState_ = StageState::Rewind;
	switch (stageState_)
	{
	case Stage2_3Scene::Game:
		NumberChange();
		if (game_manager_->GetItemCount() == gearCounter_2_3)
		{
			stageState_ = Result;
			AudioManager::GetInstance()->Stop(SoundLabel_StageBGM);
		}
		// ポーズ画面に移動
		if (input.GetKeyTrigger(VK_P))
		{
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Paused);	// 稼働コンテナのオブジェクトを全てポーズ状態に
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			}
			pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			stageState_ = Pouse;
		}
		break;
	case Stage2_3Scene::Result:
		game_manager_->TransitionToScene(SceneName::Result);
		break;
	case Stage2_3Scene::Pouse:
		// ここにポーズ画面での操作を
		if (input.GetKeyTrigger(VK_P))
		{
			for (auto& it : game_manager_->GetGameObjects())
			{
				isWindowOpen = false;
				it->SetState(GameObject::State::Active);	// 稼働コンテナのオブジェクトを全てポーズ状態に
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			stageState_ = Game;
		}
		PauseWindow();
		break;
	case Stage2_3Scene::Rewind:
		game_manager_->ResetItemCount();
		game_manager_->TransitionToScene(SceneName::Stage2_3);
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void Stage2_3Scene::Uninit()
{
}
