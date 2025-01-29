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
	backdrop_ = new Revolution(game_manager_, "result_backdrop");
	backdrop_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_ribbon_ = new Revolution(game_manager_, "result_front_ribbon");
	result_ribbon_->GetTransformComponent()->SetSize(1920.0f, 1080.0f);
	result_buttons_[0] = new Revolution(game_manager_, "result_select");
	result_buttons_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[0]->GetTransformComponent()->SetPosition(-443.0f, -300.0f);
	result_buttons_[1] = new Revolution(game_manager_, "result_next");
	result_buttons_[1]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	result_buttons_[1]->GetTransformComponent()->SetPosition(464.0f, -300.0f);
	// �M�A�t���[����Ǎ�
	for (auto& it : result_gear_frame_)
	{
		it = new Revolution(game_manager_, "result_gear_frame", "result_gear_frame");
		it->GetTransformComponent()->SetSize(200.0f, 200.0f);
		it->GetTransformComponent()->SetPosition(0.0f, -1.0f);
	}
	// �M�A�摜��Ǎ�
	for (auto& it : result_gear_)
	{
		it = new Revolution(game_manager_, "result_gear", "result_gear");
		it->GetTransformComponent()->SetSize(200.0f, 200.0f);
		it->GetTransformComponent()->SetPosition(0.0f, -1.0f);
	}
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
	if (old_scene_name_ == "Stage1_4")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage2_1);
			};
	}
	if (old_scene_name_ == "Stage2_1")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage2_2);
			};
	}
	if (old_scene_name_ == "Stage2_2")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage2_3);
			};
	}
	if (old_scene_name_ == "Stage2_3")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage2_4);
			};
	}
	if (old_scene_name_ == "Stage2_4")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage3_1);
			};
	}
	if (old_scene_name_ == "Stage3_1")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage3_2);
			};
	}
	if (old_scene_name_ == "Stage3_2")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage3_3);
			};
	}
	if (old_scene_name_ == "Stage3_3")
	{
		func = [this]() {
			game_manager_->ChangeScene(SceneName::Stage3_4);
			};
	}
	if (old_scene_name_ == "Stage3_4")
	{
		// �Ō�̃X�e�[�W�͓���ȃ��U���g�H
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
	if (!isStart_)
	{
		// �X�e�[�W���Ƃɐݒ肳�ꂽ�M�A���ɂ���Ĕz�u���Œ肷��
		switch (oldGearMaxNum_)
		{
		case 1:
			for (int i = oldGearMaxNum_; i < 5; i++)
			{
				result_gear_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
				result_gear_frame_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
			}
			break;
		case 2:
			for (int i = oldGearMaxNum_; i < 5; i++)
			{
				result_gear_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
				result_gear_frame_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
			}
			result_gear_[0]->GetTransformComponent()->SetPosition(-138.0f, -1.0f);
			result_gear_frame_[0]->GetTransformComponent()->SetPosition(-138.0f, -1.0f);
			result_gear_[1]->GetTransformComponent()->SetPosition(140.0f, -1.0f);
			result_gear_frame_[1]->GetTransformComponent()->SetPosition(140.0f, -1.0f);
			break;
		case 3:
			for (int i = oldGearMaxNum_; i < 5; i++)
			{
				result_gear_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
				result_gear_frame_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
			}
			result_gear_	  [1]->GetTransformComponent()->SetPosition(220.0f, -1.0f);
			result_gear_frame_[1]->GetTransformComponent()->SetPosition(220.0f, -1.0f);
			result_gear_	  [2]->GetTransformComponent()->SetPosition(-220.0f, -1.0f);
			result_gear_frame_[2]->GetTransformComponent()->SetPosition(-220.0f, -1.0f);
			break;
		case 4:
			for (int i = oldGearMaxNum_; i < 5; i++)
			{
				result_gear_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
				result_gear_frame_[i]->GetComponent<SpriteComponent>()->SetState(RenderComponent::State::notDraw);
			}
			result_gear_	  [0]->GetTransformComponent()->SetPosition(-340.0f, -1.0f);
			result_gear_frame_[0]->GetTransformComponent()->SetPosition(-340.0f, -1.0f);
			result_gear_	  [1]->GetTransformComponent()->SetPosition( 115.0f, -1.0f);
			result_gear_frame_[1]->GetTransformComponent()->SetPosition( 115.0f, -1.0f);
			result_gear_	  [2]->GetTransformComponent()->SetPosition(-115.0f, -1.0f);
			result_gear_frame_[2]->GetTransformComponent()->SetPosition(-115.0f, -1.0f);
			result_gear_	  [3]->GetTransformComponent()->SetPosition( 340.0f, -1.0f);
			result_gear_frame_[3]->GetTransformComponent()->SetPosition( 340.0f, -1.0f);
			break;
		case 5:
			result_gear_	  [0]->GetTransformComponent()->SetPosition( 0.0f, -1.0f);
			result_gear_frame_[0]->GetTransformComponent()->SetPosition( 0.0f, -1.0f);
			result_gear_	  [1]->GetTransformComponent()->SetPosition(-220.0f, -1.0f);
			result_gear_frame_[1]->GetTransformComponent()->SetPosition(-220.0f, -1.0f);
			result_gear_	  [2]->GetTransformComponent()->SetPosition(-440.0f, -1.0f);
			result_gear_frame_[2]->GetTransformComponent()->SetPosition(-440.0f, -1.0f);
			result_gear_	  [3]->GetTransformComponent()->SetPosition( 220.0f, -1.0f);
			result_gear_frame_[3]->GetTransformComponent()->SetPosition( 220.0f, -1.0f);
			result_gear_	  [4]->GetTransformComponent()->SetPosition( 440.0f, -1.0f);
			result_gear_frame_[4]->GetTransformComponent()->SetPosition( 440.0f, -1.0f);
			break;
		default:
			break;
		}
		isStart_ = true;
	}
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_RIGHT) || input.GetButtonTrigger(XINPUT_RIGHT))
		select_button_++;
	if (input.GetKeyTrigger(VK_LEFT) || input.GetButtonTrigger(XINPUT_LEFT))
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
	if (input.GetKeyTrigger(VK_RETURN) || input.GetButtonTrigger(XINPUT_A))
	{
		select_button_functions_[select_button_]();	// �{�^���̊֐������s
	}
}