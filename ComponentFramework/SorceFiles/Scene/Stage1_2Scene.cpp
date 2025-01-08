#include "Stage1_2Scene.h"
#include "../GameManager.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/Player.h"

#include "../GameObjects/Component/TransformComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_2Scene::Stage1_2Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_2")
	, state_(Game)
{
	this->Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_2Scene::~Stage1_2Scene()
{
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_2Scene::Init()
{
	auto obj = new Player(game_manager_);
	obj->GetTransformComponent()->SetSize(1920.0f, 1080.0f);

	state_ = Game;
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage1_2Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage1_2Scene::Game:
		if (game_manager_->GetItemCount() == gearCounter || input.GetKeyTrigger(VK_RETURN))	// �f�o�b�O�p
		{
			state_ = Result;
		}
		break;
	case Stage1_2Scene::Result:
		if (input.GetKeyTrigger(VK_RETURN))	// �f�o�b�O�p
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
// �I������
//--------------------------------------------------
void Stage1_2Scene::Uninit()
{
}
