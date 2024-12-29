#include "Stage1_5Scene.h"
#include "../GameManager.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_5Scene::Stage1_5Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_5")
	, state_(Game)
{
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_5Scene::~Stage1_5Scene()
{
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_5Scene::Init()
{
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage1_5Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage1_5Scene::Game:
		if (game_manager_->GetItemCount() == gearCounter || input.GetKeyTrigger(VK_RETURN))
		{
			state_ = Result;
		}
		break;
	case Stage1_5Scene::Result:
		if (input.GetKeyTrigger(VK_RETURN))	// �f�o�b�O�p
			game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage1_5Scene::Pouse:
		break;
	case Stage1_5Scene::Rewind:
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage1_5Scene::Uninit()
{
}
