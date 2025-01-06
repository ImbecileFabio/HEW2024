#include "Stage1_2Scene.h"
#include "../GameManager.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/Player.h"

#include "../GameObjects/Component/TransformComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Stage1_2Scene::Stage1_2Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_2")
	, state_(Game)
{
	this->Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Stage1_2Scene::~Stage1_2Scene()
{
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Stage1_2Scene::Init()
{
	auto obj = new Player(game_manager_);
	obj->GetTransformComponent()->SetSize(1920.0f, 1080.0f);

	state_ = Game;
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Stage1_2Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage1_2Scene::Game:
		if (game_manager_->GetItemCount() == gearCounter || input.GetKeyTrigger(VK_RETURN))	// デバッグ用
		{
			state_ = Result;
		}
		break;
	case Stage1_2Scene::Result:
		if (input.GetKeyTrigger(VK_RETURN))	// デバッグ用
			game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage1_2Scene::Pouse:
		break;
	case Stage1_2Scene::Rewind:
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void Stage1_2Scene::Uninit()
{
}
