//==================================================
// [ResultScene.cpp] ���U���g�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���U���g���Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "ResultScene.h"

#include "../GameManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
ResultScene::ResultScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "ResultScene")
{
	camera_ = new Camera(game_manager_);
	backdrop_ = new Revolution(game_manager_, "result_backdrop", "result_backdrop");
	backdrop_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_ribbon_ = new Revolution(game_manager_, "result_front_ribbon", "result_front_ribbon");
	result_ribbon_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_buttons_[0] = new Revolution(game_manager_, "result_select", "result_select");
	result_buttons_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[0]->GetTransformComponent()->SetPosition(-443.0f, -300.0f);
	result_buttons_[1] = new Revolution(game_manager_, "result_next", "result_next");
	result_buttons_[1]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[1]->GetTransformComponent()->SetPosition(464.0f, -300.0f);

	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
ResultScene::~ResultScene()
{

}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void ResultScene::Init()
{
	std::function<void()> func = []() {};	// ������
	if (old_scene_name_ == "Stage1_1")	// ���U���g�̑O�̃V�[���ɂ���Ď��̃V�[����ύX
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_2);
			};
	}
	if (old_scene_name_ == "Stage1_2")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_3);
			};
	}
	if (old_scene_name_ == "Stage1_3")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_4);
			};
	}
	select_button_functions_[0] = [this]() {	// �{�^���Ɋ֐���o�^
		game_manager_->ChangeScene(SceneName::Title);
		};
	select_button_functions_[1] = [func]() {	// if�̌��ʂ���
		func();
		};

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void ResultScene::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void ResultScene::Update()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_RIGHT))
		select_button_++;
	if (input.GetKeyTrigger(VK_LEFT))
		select_button_--;
	if (select_button_ > 1)	// �܂�Ԃ�����
		select_button_ = 0;
	if (select_button_ < 0)
		select_button_ = 1;
	// �S�{�^���̐F���X�V
	for (int i = 0; i < result_buttons_.size(); ++i)
	{
		if (i == select_button_)
		{
			// �I�𒆂̃{�^���̐F��ύX
			result_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
		}
		else
		{
			// ���I���̃{�^���̐F�����ɖ߂�
			result_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	if (input.GetKeyTrigger(VK_RETURN))
	{
		select_button_functions_[select_button_]();	// �{�^���̊֐������s
	}

}
