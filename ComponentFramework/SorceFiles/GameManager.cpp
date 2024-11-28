//=================================================================
// [GameManager.cpp] �Q�[���}�l�[�W���[���W���[�� 
// ���ҁF�L�n�[��
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
#include "Renderer.h"
#include "ImGuiManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/GameObject/Player.h"
#include "GameObjects/GameObject/Camera.h"
#include "GameObjects/GameObject/Pendulum.h"

// �f�o�b�O�悤���Ԃ���������
#include "GameObjects/GameObject/TestObject.h"
#include "GameObjects/GameObject/ColliderTestObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"

//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
GameManager::GameManager()
	:updating_game_objects_(false)
{
	std::cout << std::format("[GameManager] -> Constructor\n");
	this->InitAll();

}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	this->UninitAll();
	std::cout << std::format("[GameManager] -> Destructor\n");
}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << std::format("[GameManager] -> InitAll Start\n");

	// �����_���[������
	renderer_ = new Renderer();
	renderer_->Init();

	game_objects_.clear();
	pending_game_objects_.clear();


    // �Q�[���I�u�W�F�N�g������
	camera_ = new Camera(this);
    //player_ = new Player(this);
	test_object_ = new TestObject(this);
	//pendulum_ = new Pendulum(this);
}

//-----------------------------------------------------------------
// �I������
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << std::format("[GameManager] -> UninitAll Start\n");

	// �Q�[���I�u�W�F�N�g�̔j��
	delete renderer_;
	delete camera_;
	delete player_;

	delete test_object_;
	//delete pendulum_;
	

	//std::cout << std::format("[GameManager] -> �Z�[�u�f�[�^�̃A�����[�h\n");
	//std::cout << std::format("[GameManager] -> �O���t�B�b�N�X�̔j��\n");
}

//-----------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// �Q�[���I�u�W�F�N�g�̍X�V
	this->UpdateGameObjects();
	ImGuiManager::staticPointer->ImGuiShowWindow(this->game_objects_);
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
	collider_game_objects_.clear();	// Clear���Ȃ��Ə�����������

	for (auto& gameObject : game_objects_)
	{
		gameObject->Update();		// �X�V����
		if (gameObject->GetComponent<CircleColliderComponent>())
		{
			collider_game_objects_.emplace_back(gameObject);
		}
	}
	// �����蔻��R���e�i�ŏ���
	for (int i = 0; i < collider_game_objects_.size(); i++)
	{
		for (int j = i + 1; j < collider_game_objects_.size(); j++)
		{
			collider_game_objects_[i]->GetComponent<CircleColliderComponent>()->
				CheckCollisionCollider(collider_game_objects_[j]->GetComponent<CircleColliderComponent>());
		}
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