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
#include "../GameObjects/Component/ChildrenComponent.h"

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
	tile_ = new Tile(game_manager_);
	robot_ = new Robot(game_manager_);
	pendulum_ = new Pendulum(game_manager_, 30.f, Vector3(0, 0, 0), true);
	pendulum_2_ = new Pendulum(game_manager_, 30.f, Vector3(400, 0, 0), true);
	pendulum_3_ = new Pendulum(game_manager_, 30.f, Vector3(-400, 0, 0), true);
	lift_ = new Lift(Lift::MoveState::side, { 100.0f, 0.0f, 0.0f }, { -100.0f, 0.0f, 0.0f }, game_manager_);

	items_.resize(2, nullptr);
	items_[0] = new Item(game_manager_);
	items_[0]->GetComponent<TransformComponent>()->SetScale(100.0f , 100.0f);
	items_[1] = new Item(game_manager_);
	items_[1]->GetComponent<TransformComponent>()->SetScale(100.0f, 100.0f);

	State = Game;

	for (auto& colliderObjects : game_manager_->GetGameObjects())
	{
		auto children = colliderObjects->GetComponent<ChildrenComponent>();
		if (children)
		{
			for (auto& childrenColliderObjects : children->GetChildren())
			{
				auto childrenColliderComponent = childrenColliderObjects->GetComponent<ColliderBaseComponent>();
				if (childrenColliderComponent)
					game_manager_->GetColliderManager()->AddGameObject(childrenColliderObjects);
			}
		}
		// �����蔻��̂���I�u�W�F�N�g���R���C�_�[�}�l�[�W���[�ɓo�^
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
	delete pendulum_2_;
	delete pendulum_3_;
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
		std::cout << std::format("1 {}\n", pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumLength());
		std::cout << std::format("2 {}\n", pendulum_2_->GetComponent<PendulumMovementComponent>()->GetPendulumLength());
		std::cout << std::format("3 {}\n", pendulum_3_->GetComponent<PendulumMovementComponent>()->GetPendulumLength());
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
