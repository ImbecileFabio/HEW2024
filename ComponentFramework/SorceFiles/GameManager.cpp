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
#include "Renderer.h"
#include "AudioManager.h"
#include "ImGuiManager.h"
#include "PemdulumManager.h"


//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	std::cout << std::format("[GameManager] -> Constructor\n");
	// �����_���[������
	renderer_ = new Renderer();
	renderer_->Init();

	// �I�[�f�B�I�}�l�[�W���[������
	//audio_manager_ = new AudioManager();

	// �R���C�_�[�}�l�[�W���[������
	collider_manager_ = ColliderManager::Create();

	// �U��q�}�l�[�W���[������
	pendulum_manager_ = PendulumManager::GetInstance();

	this->InitAll();
}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	// �������
	std::cout << std::format("[GameManager] -> Destructor\n");
	this->UninitAll();

	delete current_scene_;
	delete renderer_;
	delete audio_manager_;
	delete collider_manager_;

}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << std::format("[GameManager] -> InitAll Start\n");



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
	std::cout << std::format("[GameManager] -> UninitAll Start\n");

	// �Q�[���I�u�W�F�N�g�̔j��
	this->ClearAllObjects();
}

//-----------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// �Q�[���I�u�W�F�N�g�̍X�V
	this->current_scene_->Update();
	this->UpdateGameObjects();
	this->collider_manager_->UpdateAll();
	this->pendulum_manager_->Update();
	ImGuiManager::staticPointer->ImGuiShowWindow();
}
//-----------------------------------------------------------------
// �o�͐�������
//-----------------------------------------------------------------
void GameManager::GenerateOutputAll(void)
{
	if(renderer_)
	{

		renderer_->Begin();
		renderer_->Draw();

		ImGuiManager::staticPointer->ImGuiRender();	// ImGui�̃E�B���h�E��`��

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
	std::cout << "�N���A�I�[���I�u�W�F�N�g\n";

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
		std::cout << std::format("\n[{}] -> delete\n", obj->GetObjectName());
		delete obj;
	}

	// �Q�[���I�u�W�F�N�g���X�g���N���A
	game_objects_.clear();
}


//-----------------------------------------------------------------
// �V�[���؂�ւ�����
//-----------------------------------------------------------------
void GameManager::ChangeScene(SceneName _scene) {
	std::cout << "\n[GameManager] -> ChangeScene\n";

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
		switch (_scene) {
		case Title:
			current_scene_ = new TitleScene(this);
			break;
		case Stage1_1:
			current_scene_ = new Stage1_1Scene(this);
			break;
		case Result:
			itemCount = 0;
			current_scene_ = new ResultScene(this);
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
void GameManager::UpdateGameObjects(void)
{
	// ���ׂẴQ�[���I�u�W�F�N�g�̍X�V
	updating_game_objects_ = true;

	for (auto& gameObject : game_objects_)
	{
		gameObject->Update();		// �X�V����
	}
	updating_game_objects_ = false;

	// �ҋ@���X�g�̃Q�[���I�u�W�F�N�g�̑���
	for (auto& pendingGameObject : pending_game_objects_)
	{
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