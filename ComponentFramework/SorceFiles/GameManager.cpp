//=================================================================
// [GameManager.cpp] �Q�[���}�l�[�W���[���W���[�� 
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Q�[���̏�ԂƃI�u�W�F�N�g�̊Ǘ��A�ǉ��ƍ폜�A���́A�X�V�A�`��Ȃ�
//=================================================================

/*----- �C���N���[�h -----*/
#include "StdAfx.h"
#include "GameManager.h"
#include "Renderer.h"
#include "GameObjects/GameObject/Player.h"
#include "GameObjects/GameObject/Camera.h"



//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
GameManager::GameManager()
	: updating_game_objects_(false)
{
	std::cout << "[�Q�[���}�l�[�W���[] -> �N��\n";
	this->InitAll();

}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
GameManager::~GameManager(void)
{
	this->UninitAll();
	std::cout << "[�Q�[���}�l�[�W���[] -> ��~\n";
}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void GameManager::InitAll(void)
{
	std::cout << "[�Q�[���}�l�[�W���[] -> ����������\n";

	game_objects_.clear();
	pending_game_objects_.clear();

	// �����_���[������
	renderer_ = std::make_unique<Renderer>();
	renderer_->Init();

	// �Q�[���I�u�W�F�N�g������
	//player_ = std::make_unique<Player>(this);
	//camera_ = std::make_unique<Camera>(this);
}

//-----------------------------------------------------------------
// �I������
//-----------------------------------------------------------------
void GameManager::UninitAll(void)
{
	std::cout << "[�Q�[���}�l�[�W���[] -> ���\�[�X�J���J�n\n";

	if (renderer_)
	{
		renderer_->Uninit();
	}

	game_objects_.clear();

	std::cout << "[�Q�[���}�l�[�W���[] -> ���\�[�X�J���I��\n";



	std::cout << "[�Q�[���}�l�[�W���[] -> �Z�[�u�f�[�^�̃A�����[�h\n";
	std::cout << "[�Q�[���}�l�[�W���[] -> �O���t�B�b�N�X�̔j��\n";
}

//-----------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------
void GameManager::UpdateAll()
{
	// �Q�[���I�u�W�F�N�g�̍X�V
	this->UpdateGameObjects();
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
		renderer_->End();
	}
}

//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̒ǉ�����
//-----------------------------------------------------------------
void GameManager::AddGameObject(GameObject* gameObject)
{
	// �Q�[���I�u�W�F�N�g�̍X�V�����œo�^���ύX
	if (updating_game_objects_)
		pending_game_objects_.emplace_back(gameObject);	// �ҋ@�R���e�i
	else
		game_objects_.emplace_back(gameObject);			// �ғ��R���e�i
}

//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̍폜����
//-----------------------------------------------------------------

void GameManager::RemoveGameObject(GameObject* gameObject)
{
	// �ҋ@�R���e�i
	// "gameObject"���R���e�i�̒�����T���o���Ĕj��
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), gameObject);
	if (iter != game_objects_.end())
	{
		// ��v����"gameObject"���R���e�i�̖����ֈړ������A���������̂�j������
		std::ranges::iter_swap(iter, game_objects_.end() - 1);
		game_objects_.pop_back();
	}
}


//-----------------------------------------------------------------
// �Q�[���I�u�W�F�N�g�̑��X�V����
//-----------------------------------------------------------------
/*-----  �Q�[���I�u�W�F�N�g -----*/
void GameManager::UpdateGameObjects(void)
{
	// ���ׂẴQ�[���I�u�W�F�N�g�̍X�V
	updating_game_objects_ = true;
	for (auto& game_object : game_objects_)
		game_object->Update();
	updating_game_objects_ = false;

	// �ҋ@���X�g�̃Q�[���I�u�W�F�N�g�̑���
	for (auto& pending_game_object : pending_game_objects_)
	{
		pending_game_object->Update();
		game_objects_.emplace_back(pending_game_object);
	}

}
