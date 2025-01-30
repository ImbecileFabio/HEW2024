//=================================================================
// [GameManager.cpp] �Q�[���}�l�[�W���[���W���[�� 
// ���ҁFKeita Arima
//-----------------------------------------------------------------
// �����F�Q�[���̏�ԂƃI�u�W�F�N�g�̊Ǘ��A�ǉ��ƍ폜�A���́A�X�V�A�`��Ȃ�
//=================================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>

#include "GameManager.h"
#include "ColliderManager.h"
#include "ImGuiManager.h"
#include "PemdulumManager.h"
#include "TextureManager.h"
#include "FadeManager.h"

#include "Renderer.h"

#include "GameObjects/GameObject.h"

//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	// �����_���[������
	renderer_ = new Renderer();
	renderer_->Init();

	// �e�N�X�`���̃��[�h
	TextureManager::GetInstance().Init();

	// �t�F�[�h�}�l�[�W��������
	fade_manager_ = new FadeManager(this);

	// �R���C�_�[�}�l�[�W���[������
	collider_manager_ = ColliderManager::Create();
	
	// �U��q�}�l�[�W���[������
	pendulum_manager_ = PendulumManager::GetInstance();
	pendulum_manager_->SetGM(this);
	this->InitAll();
}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	// �������
	this->UninitAll();

	delete current_scene_;
	delete renderer_;
	delete collider_manager_;
	delete pendulum_manager_;
	delete fade_manager_;
}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	// �I�u�W�F�N�g���X�g�̏�����
	game_objects_.clear();
	pending_game_objects_.clear();
	// �V�[���̏�����
	current_scene_ = new TitleScene(this);
    // �Q�[���I�u�W�F�N�g������
	current_scene_->Init();

	ImGuiManager::staticPointer->SetObjectList(game_objects_);
}

//-----------------------------------------------------------------
// �I������
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	// �Q�[���I�u�W�F�N�g�̔j��
	this->ClearAllObjects();
}

//-----------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------
void GameManager::UpdateAll(float _deltaTime)
{
	// �t�F�[�h�}�l�[�W���̍X�V
	fade_manager_->Update(_deltaTime);

	// �Q�[���I�u�W�F�N�g�̍X�V
	this->current_scene_->Update();
	this->UpdateGameObjects(_deltaTime);
	this->collider_manager_->UpdateAll();
	this->pendulum_manager_->Update();
	ImGuiManager::staticPointer->ImGuiShowWindow();
}

//-----------------------------------------------------------------
// �o�͐�������
//-----------------------------------------------------------------
void GameManager::GenerateOutputAll(void)
{
	if (renderer_)
	{

		renderer_->Begin();
		renderer_->Draw();

		fade_manager_->Draw();

		ImGuiManager::staticPointer->ImGuiRender();

		renderer_->End();

	}
}

//-----------------------------------------------------------------
// @biref �I�u�W�F�N�g�����ׂăN���A
//	��xdeadgameobjects�Ɉړ������Ă���������邱�ƂŃC�e���[�^���o�O��̂�h���ł܂�
// �igameobject�̓f�X�g���N�^��gameobjects���珟��ɏo�Ă����̂ł����j
//-----------------------------------------------------------------
void GameManager::ClearAllObjects(void)
{
	// �U��q�}�l�[�W���ƃR���C�_�[�}�l�[�W���̏�����
	pendulum_manager_->Uninit();
	collider_manager_->UninitAll();

	// �폜�Ώۃ��X�g���쐬
	std::vector<GameObject*> dead_game_objects;

	// �ғ����̃Q�[���I�u�W�F�N�g���폜�Ώۃ��X�g�ɒǉ�
	for (auto& obj : game_objects_) {
		dead_game_objects.push_back(obj);
	}
	// �ҋ@���̃Q�[���I�u�W�F�N�g���폜�Ώۃ��X�g�ɒǉ�
	for (auto& obj : pending_game_objects_){
		dead_game_objects.push_back(obj);
	}

	// �폜�Ώۃ��X�g���̃I�u�W�F�N�g�����S�ɍ폜
	for (auto& obj : dead_game_objects) {
		delete obj;
	}

	// �Q�[���I�u�W�F�N�g���X�g���N���A
	game_objects_.clear();
}

//-----------------------------------------------------------------
// @param ���̃V�[����
// @breaf �V�[���؂�ւ��鎞�Ƀt�F�[�h�C���E�A�E�g���s��
//			�t�F�[�h�A�E�g���I����changescene���Ăяo��
//-----------------------------------------------------------------
void GameManager::TransitionToScene(SceneName _nextScene)
{
	if (fade_manager_->GetIsPlaying()) {
		return; // �t�F�[�h���Ȃ��d���s��h��
	}

	// �t�F�[�h�A�E�g�J�n
	fade_manager_->StartFadeOut("fade_out", [this, _nextScene]() {

		// �t�F�[�h�A�E�g�I�����ɃV�[����؂�ւ�
		ChangeScene(_nextScene);


		// �V�[���ύX��Ƀt�F�[�h�C�����J�n
		fade_manager_->StartFadeIn("fade_in");

		});
}

//-----------------------------------------------------------------
// @param ���̃V�[����
// @breaf �V�[���؂�ւ�����
//-----------------------------------------------------------------
void GameManager::ChangeScene(SceneName _nextScene) 
{



// �O�̃V�[������ۑ����Ă���
	std::string old_scene_name = current_scene_->GetSceneName();
	// �O�̃V�[���̃M�A�l������ۑ�
	int gearMaxCount = current_scene_->GetGearMaxCount();
	// ���݂̃V�[���̏I������
	if (current_scene_) {
		try {
			current_scene_->Uninit();
			delete current_scene_;
		}
		catch (const std::exception& e) {
			std::cerr << "[ChangeScene] -> ��O : " << e.what() << std::endl;
		}
		current_scene_ = nullptr;
	}

	// �Q�[���I�u�W�F�N�g�̑S�폜
	try {
		ClearAllObjects();
	}
	catch (const std::exception& e) {
		std::cerr << "[ClearAllObjects] -> ��O : " << e.what() << std::endl;
	}




	// �V�����V�[���̏�����
	try {
		switch (_nextScene) {
		case Title:
			current_scene_ = new TitleScene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_1:
			current_scene_ = new Stage1_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_2:
			current_scene_ = new Stage1_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_3:
			current_scene_ = new Stage1_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage1_4:
			current_scene_ = new Stage1_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_1:
			current_scene_ = new Stage2_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_2:
			current_scene_ = new Stage2_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_3:
			current_scene_ = new Stage2_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage2_4:
			current_scene_ = new Stage2_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_1:
			current_scene_ = new Stage3_1Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_2:
			current_scene_ = new Stage3_2Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_3:
			current_scene_ = new Stage3_3Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Stage3_4:
			current_scene_ = new Stage3_4Scene(this);
			current_scene_->SetOldSceneName(old_scene_name);
			break;
		case Result:
		{
			itemCount = 0;
			current_scene_ = new ResultScene(this);
			auto result = dynamic_cast<ResultScene*>(current_scene_);
			result->SetGearMaxNum(gearMaxCount);
			current_scene_->SetOldSceneName(old_scene_name);
			current_scene_->Init();
		}
			break;
		default:
			std::cout << std::format("[GameManager] -> ChangeScene Error\n");
			break;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[ChangeScene] -> ��O : " << e.what() << std::endl;
	}


	ImGuiManager::staticPointer->ResetSelectObject();
}


//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̒ǉ�����
//-----------------------------------------------------------------
void GameManager::AddGameObject (GameObject* gameObject)
{
	// �Q�[���I�u�W�F�N�g�̍X�V�����œo�^���ύX
	if (updating_game_objects_)
	{
		pending_game_objects_.emplace_back(gameObject);	// �ҋ@�R���e�i
	}
	else
	{
		game_objects_.emplace_back(gameObject);			// �ғ��R���e�i
	}
}

//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̍폜����
//-----------------------------------------------------------------
/*
* @param	�폜����Q�[���I�u�W�F�N�g
* @brief	�R���e�i�̒�����폜����I�u�W�F�N�g��T���č폜����
*/
void GameManager::RemoveGameObject(GameObject* _gameObject) {
	// �ҋ@�R���e�i
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), _gameObject);
	if (iter != pending_game_objects_.end())
	{
		std::iter_swap(iter, pending_game_objects_.end() - 1);	// �R���e�i�̍Ō���Ɠ���ւ�
		pending_game_objects_.pop_back();						// �ҋ@�R���e�i����폜

	}

	// �ғ��R���e�i
	iter = std::find(game_objects_.begin(), game_objects_.end(), _gameObject);
	if (iter != game_objects_.end())
	{
		std::iter_swap(iter,game_objects_.end() - 1);	// �R���e�i�̍Ō���Ɠ���ւ�
		game_objects_.pop_back();						// �ғ��R���e�i����폜
	}

}
//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̑��X�V����
//-----------------------------------------------------------------
void GameManager::UpdateGameObjects(float _deltaTime)
{
	// ���ׂẴQ�[���I�u�W�F�N�g�̍X�V
	updating_game_objects_ = true;
	for (auto& gameObject : game_objects_)
	{
		gameObject->SetDeltaTime(_deltaTime);	// �f���^�^�C���̐ݒ�
		gameObject->Update();		// �X�V����
	}
	updating_game_objects_ = false;

	// �ҋ@���X�g�̃Q�[���I�u�W�F�N�g�̑���
	for (auto& pendingGameObject : pending_game_objects_)
	{
		pendingGameObject->SetDeltaTime(_deltaTime);
		pendingGameObject->Update();
		game_objects_.emplace_back(pendingGameObject);
	}
	pending_game_objects_.clear();

	// �Q�[���I�u�W�F�N�g���j����Ԃ��`�F�b�N
	std::vector<GameObject*> dead_game_objects;
	for (auto& gameObject : game_objects_)
	{
		if (gameObject->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(gameObject);
		}
	}
}