//==================================================
// [Stage1_1Scene.cpp] �X�e�[�W1-1�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-1���Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "Stage1_1Scene.h"

#include "../GameManager.h"
#include "../ColliderManager.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/Player.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Pendulum.h"
#include "../GameObjects/GameObject/Tile.h"
#include "../GameObjects/GameObject/Robot.h"

// �f�o�b�O�悤���Ԃ���������
#include "../GameObjects/GameObject/TestObject.h"
#include "../GameObjects/GameObject/ColliderTestObject.h"
#include "../GameObjects/Component/ColliderComponent/CircleColliderComponent.h"

//==================================================
// �R���X�g���N�^
//==================================================
Stage1_1Scene::Stage1_1Scene(GameManager* _gameManager)
	: SceneBase(_gameManager)
{
	this->Init();
}

//==================================================
// �f�X�g���N�^
//==================================================
Stage1_1Scene::~Stage1_1Scene()
{
	this->Uninit();
}

//==================================================
// ����������
//==================================================
void Stage1_1Scene::Init()
{
	camera_ = new Camera(game_manager_);
	//player_ = new Player(game_manager_);
	test_object_ = new TestObject(game_manager_);
	tile_ = new Tile(game_manager_);
	robot_ = new Robot(game_manager_);

	pendulum_ = new Pendulum(game_manager_);
	// 
	// GameManeger�Ő������āAColliderManager�ɓo�^����
	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{	// �����蔻��̂���I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
		if (colliderObjects->GetComponent<ColliderBaseComponent>())
		{
			game_manager_->GetColliderManager()->AddGameObject(colliderObjects);
		}
	}

}

//==================================================
// �I������
//==================================================
void Stage1_1Scene::Uninit()
{
	delete camera_;

	delete test_object_;
	//delete player_ ;
	delete pendulum_;
	delete tile_;
	delete robot_;

}

//==================================================
// �X�V����
//==================================================
void Stage1_1Scene::Update()
{

}
