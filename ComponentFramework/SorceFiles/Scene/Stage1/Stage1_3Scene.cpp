#include "Stage1_3Scene.h"
#include "../../GameManager.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Stage1_3Scene::Stage1_3Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_3")
	, state_(Game)
{
	Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Stage1_3Scene::~Stage1_3Scene()
{
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Stage1_3Scene::Init()
{
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Stage1_3Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage1_3Scene::Game:
		if (game_manager_->GetItemCount() == gearCounter || input.GetKeyTrigger(VK_RETURN))
		{
			state_ = Result;
		}
		break;
	case Stage1_3Scene::Result:
		if (input.GetKeyTrigger(VK_RETURN))	// デバッグ用
			game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage1_3Scene::Pouse:
		break;
	case Stage1_3Scene::Rewind:
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void Stage1_3Scene::Uninit()
{
}
