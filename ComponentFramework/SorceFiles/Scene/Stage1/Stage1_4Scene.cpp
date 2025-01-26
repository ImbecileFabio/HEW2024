#include "Stage1_4Scene.h"
#include "../../GameManager.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_4Scene::Stage1_4Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_4")
	, state_(Game)
{
	Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_4Scene::~Stage1_4Scene()
{
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_4Scene::Init()
{
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage1_4Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage1_4Scene::Game:
		if (game_manager_->GetItemCount() == gearCounter || input.GetKeyTrigger(VK_RETURN))
		{
			state_ = Result;
		}
		break;
	case Stage1_4Scene::Result:
		if (input.GetKeyTrigger(VK_RETURN))	// �f�o�b�O�p
			game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage1_4Scene::Pouse:
		break;
	case Stage1_4Scene::Rewind:
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage1_4Scene::Uninit()
{
}
