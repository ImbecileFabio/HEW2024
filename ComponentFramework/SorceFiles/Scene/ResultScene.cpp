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
#include "../GameObjects/Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
ResultScene::ResultScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "ResultScene")
{
	camera_ = new Camera(game_manager_);
	result_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/result/v01/10.JPG");
	result_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	result_->GetComponent<TransformComponent>()->SetPosition(0.0f, 0.0f);
	select_buttons_[0] = new Revolution(game_manager_, TEXTURE_PATH_"hoge.png");
	select_buttons_[0]->GetTransformComponent()->SetSize(400.0f, 200.0f);
	select_buttons_[0]->GetTransformComponent()->SetPosition(-400.0f, -300.0f);
	select_buttons_[1] = new Revolution(game_manager_, TEXTURE_PATH_"hoge.png");
	select_buttons_[1]->GetTransformComponent()->SetSize(400.0f, 200.0f);
	select_buttons_[1]->GetTransformComponent()->SetPosition(400.0f, -300.0f);
	//this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
ResultScene::~ResultScene()
{
	delete camera_;
	delete result_;
	for (auto& select_button : select_buttons_)
	{
		select_button->Uninit();
	}
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void ResultScene::Init()
{
	std::function<void()> func = []() {};	// ������
	if (old_scene_name_ == "Stage1_1")
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
	if (old_scene_name_ == "Stage1_4")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage1_5);
			};
	}
	select_button_functions_[0] = [this]() {
		game_manager_->ChangeScene(SceneName::Title);
		};
	select_button_functions_[1] = [func]() {
		func();
		};
}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void ResultScene::Uninit()
{
	delete camera_;
	delete result_;
	for (auto& select_button : select_buttons_)
	{
		select_button->Uninit();
	}
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
	for (int i = 0; i < select_buttons_.size(); ++i)
	{
		if (i == select_button_)
		{
			// �I�𒆂̃{�^���̐F��ύX
			select_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
		}
		else
		{
			// ���I���̃{�^���̐F�����ɖ߂�
			select_buttons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	if (input.GetKeyTrigger(VK_RETURN))
	{
		select_button_functions_[select_button_]();	// �{�^���̊֐������s
	}
}
