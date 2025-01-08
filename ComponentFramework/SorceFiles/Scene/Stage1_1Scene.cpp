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
#include "../InputManager.h"
#include "../TileMapManager.h"

#include "../GameObjects/Component/ColliderComponent/ColliderBaseComponent.h"
#include "../GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "../GameObjects/Component/PendulumMovementComponent.h"
#include "../GameObjects/Component/ChildrenComponent.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/GameObject/BackGround.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/GameObject/Pendulum.h"
#include "../GameObjects/GameObject/Tile.h"
#include "../GameObjects/GameObject/Robot.h"
#include "../GameObjects/GameObject/Lift.h"
#include "../GameObjects/GameObject/Item.h"
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
	camera_ = new Camera(game_manager_);
	back_ground_ = new BackGround(game_manager_);

	//tile_ = new Tile(game_manager_);
	//tile_->GetTransformComponent()->SetPosition(600.0f, 50.0f);
	//tile_2_ = new Tile(game_manager_);
	//tile_2_->GetTransformComponent()->SetPosition(-200.0f, 50.0f);
	//tile_3_ = new Tile(game_manager_);
	//tile_3_->GetTransformComponent()->SetPosition(-100.0f, 50.0f);
	//robot_ = new Robot(game_manager_);
	//robot_->GetTransformComponent()->SetPosition(500.0f, 150.0f);
	//pendulum_ = new Pendulum(game_manager_, Vector3(270.0f, -60.0f, 0.0f), true, 60.0f);
	//lift_ = new Lift(game_manager_);
	//lift_->GetTransformComponent()->SetPosition(270.0f, -60.0f);
	//lift_->SetMaxPos({ 0.0f, 60.0f, 0.0f });
	//lift_->SetMinPos({ 0.0f, -100.0f, 0.0f });
	//lift_->SetMoveState(Lift::MoveState::length);
	//lift_->SetPendulum(pendulum_);

	auto mapData = tile_map_manager_->LoadCSV("MapData/Stage1_1.csv");
	tile_map_manager_->LoadTileMap(mapData);


	State = Game;

	// GameManager�Ő������āAColliderManager�ɓo�^����
	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{	// �q�I�u�W�F�N�g��ǉ�
		auto childrenComponent = colliderObjects->GetComponent<ChildrenComponent>();
		if (childrenComponent)
		{
			auto& childrenObjects = childrenComponent->GetChildren();
			for (auto& children : childrenObjects)
			{
				// �����蔻��̂���I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
				if (children->GetComponent<ColliderBaseComponent>())
				{
					game_manager_->GetColliderManager()->AddGameObject(children);
				}
			}
		}
		// �����蔻��̂���I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
		if (colliderObjects->GetComponent<ColliderBaseComponent>())
		{
			game_manager_->GetColliderManager()->AddGameObject(colliderObjects);
		}
	}

	for (auto& pendulumObject : game_manager_->GetGameObjects()) {
		auto childrenComponent = pendulumObject->GetComponent<ChildrenComponent>();
		if (childrenComponent)
		{
			auto& childrenObjects = childrenComponent->GetChildren();
			for (auto& children : childrenObjects)
			{
				// �y���f�������I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
				if (children->GetComponent<PendulumMovementComponent>())
				{
					game_manager_->GetPendulumManager()->AddGameObject(children);
				}
			}
		}
		if (pendulumObject->GetComponent<PendulumMovementComponent>()) {
			game_manager_->GetPendulumManager()->AddGameObject(pendulumObject);
		}
	}

	PendulumManager::GetInstance()->SetSelectedPendulum(PendulumManager::GetInstance()->GetPendulumList().front());
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage1_1Scene::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage1_1Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (State)
	{
	case Stage1_1Scene::Game:
		if(game_manager_->GetItemCount() == gearCounter) 
		{
		 	State = Result;
		}
		break;
	case Stage1_1Scene::Result:
		game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage1_1Scene::Pouse:
		break;
	case Stage1_1Scene::Rewind:
		break;
	default:
		break;
	}
}