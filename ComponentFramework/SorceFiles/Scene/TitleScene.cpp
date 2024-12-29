//==================================================
// [TitleScene.cpp] �^�C�g���V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C�g���̊Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "TitleScene.h"

#include "../GameManager.h"
#include "../AudioManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"

int TitleScene::create_count = 0;
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
	, state_(State::title)
{
	select_stages_ = {};	// 0�ŏ�����
	camera_ = new Camera(game_manager_);
	select_rough_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/7.JPG");
	select_rough_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	title_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/title/v01/6.JPG");
	title_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	create_count++;
	if (create_count > 1)
	{
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		state_ = State::select;
	}
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
TitleScene::~TitleScene()
{
	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void TitleScene::Init()
{
	//select_stages_[0][0] = game_manager_->ChangeScene(SceneName::Stage1_1);
	select_stages_[0][0] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_1);
		};
	select_stages_[0][1] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_2);
		};
	select_stages_[0][2] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_3);
		};
	select_stages_[0][3] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_4);
		};
	select_stages_[0][4] = [this](){
		game_manager_->ChangeScene(SceneName::Stage1_5);
		};
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void TitleScene::Uninit()
{
	delete camera_;
	delete title_;
	delete select_rough_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void TitleScene::Update()
{
	auto& input = InputManager::GetInstance();
	//game_manager_->GetAudioManager()->Play(SoundLabel_TitleBGM);
	switch (state_)
	{
	case TitleScene::State::title:
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
		if (input.GetKeyTrigger(VK_RETURN))// �Z���N�g�Ɉړ�
		{
			state_ = State::select;
		}
		break;
	case TitleScene::State::select:
		MoveSelect();
		title_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		if (input.GetKeyTrigger(VK_RETURN))	// �Q�[���X�^�[�g
		{
			StageSelect();
			//game_manager_->GetAudioManager()->Stop(SoundLabel_TitleBGM);
		}
		if (input.GetKeyTrigger(VK_X))	// �^�C�g���߂�
			state_ = State::title;
		break;
	case TitleScene::State::option:
		// �����ɃI�v�V����
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// �񎟌��z��̏�Ԃɂ���ăX�e�[�W��I��
//--------------------------------------------------
void TitleScene::StageSelect()
{
	select_stages_[chapter_][stage_]();	// �Y�����ɂ����ChangeScene���Ăт���
}
//--------------------------------------------------
// �Z���N�g�̓Y�����̓������Ǘ�����֐�
//--------------------------------------------------
void TitleScene::MoveSelect()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_R))		// R�{�^��
		chapter_++;
	if (input.GetKeyTrigger(VK_L))		// L�{�^��
		chapter_--;
	if (input.GetKeyTrigger(VK_RIGHT))	// �E
		stage_++;
	if (input.GetKeyTrigger(VK_LEFT))	// ��
		stage_--;
	// �͈͊O�̏���
	if (chapter_ > CHAPTER_MAX) chapter_ = 0;
	if (chapter_ < 0) chapter_ = 0;
	if (stage_ < 0) stage_ = 4;
	if (stage_ > STAGE_MAX) stage_ = 0;
}
