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
#include "../PemdulumManager.h"
#include "../GameObjects/Component/ColliderComponent/ColliderBaseComponent.h"
#include "../GameObjects/Component/PendulumMovementComponent.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/BackGround.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Pendulum.h"
#include "../GameObjects/GameObject/Tile.h"
#include "../GameObjects/GameObject/Robot.h"
#include "../GameObjects/GameObject/Lift.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_1Scene::Stage1_1Scene(GameManager* _gameManager)
	: SceneBase(_gameManager, "Stage1_1")
{
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_1Scene::~Stage1_1Scene()
{
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_1Scene::Init()
{
	camera_			= new Camera(game_manager_);
	back_ground_	= new BackGround(game_manager_);
	tile_			= new Tile(game_manager_);
	robot_			= new Robot(game_manager_);
	pendulum_		= new Pendulum(game_manager_, 30.f, Vector3(0, 0, 0), true);
	//pendulum_2_		= new Pendulum(game_manager_, 30.f, Vector3(400, 0, 0), true);
	//pendulum_3_		= new Pendulum(game_manager_, 30.f, Vector3(-400, 0, 0), true);
	lift_			= new Lift(Lift::MoveState::side, { 100.0f, 0.0f, 0.0f }, {-100.0f, 0.0f, 0.0f}, game_manager_);

	State = Game;
	
	// GameManeger�Ő������āAColliderManager�ɓo�^����
	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{	// �����蔻��̂���I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
		if (colliderObjects->GetComponent<ColliderBaseComponent>())
		{
			game_manager_->GetColliderManager()->AddGameObject(colliderObjects);
		}
	}

	for (auto& pemdulumObject : game_manager_->GetGameObjects()) {
		if (pemdulumObject->GetComponent<PendulumMovementComponent>()) {
			game_manager_->GetPemdulumManager()->AddGameObject(pemdulumObject);
		}
	}
	PemdulumManager::GetInstance()->SetSelectedPemdulum(PemdulumManager::GetInstance()->GetPemdulumList().front());
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage1_1Scene::Uninit()
{
	delete camera_;
	delete back_ground_;
	delete pendulum_;
	//delete pendulum_2_;
	//delete pendulum_3_;
	delete tile_;
	delete robot_;
	delete lift_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage1_1Scene::Update()
{
	switch (State)
	{
	case Stage1_1Scene::Game:
		break;
	case Stage1_1Scene::Result:
		break;
	case Stage1_1Scene::Pouse:
		break;
	case Stage1_1Scene::Rewind:
		break;
	default:
		break;
	}
}
