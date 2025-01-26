#include "Stage1_3Scene.h"
#include "../../GameManager.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_3Scene::Stage1_3Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_3")
	, state_(Game)
{
	Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_3Scene::~Stage1_3Scene()
{
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_3Scene::Init()
{
}
//--------------------------------------------------
// �X�V����
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
		if (input.GetKeyTrigger(VK_RETURN))	// �f�o�b�O�p
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
// �I������
//--------------------------------------------------
void Stage1_3Scene::Uninit()
{
}
