#include "Stage2_1Scene.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../../PemdulumManager.h"
#include "../../InputManager.h"
#include "../../TileMapManager.h"
#include "../../AudioManager.h"

#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/GameObject/Player.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/GameObject/BackGround.h"
#include "../../GameObjects/GameObject/Camera.h"
#include "../../GameObjects/GameObject/Pendulum.h"
#include "../../GameObjects/GameObject/Tile.h"
#include "../../GameObjects/GameObject/Robot.h"
#include "../../GameObjects/GameObject/Lift.h"
#include "../../GameObjects/GameObject/Item.h"
#include "../../GameObjects/GameObject/Revolution.h"
#include "../../GameObjects/GameObject/HammerCursor.h"

#include "../../GameObjects/Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "../../GameObjects/Component/PendulumMovementComponent.h"
#include "../../GameObjects/Component/ChildrenComponent.h"


constexpr int gearCounter_2_1 = 1;		// �M�A�̊l����
constexpr int hammerCounter_2_1 = 3;	// �@������
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage2_1Scene::Stage2_1Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage2_1")
	, state_(Game)
{
	Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage2_1Scene::~Stage2_1Scene()
{
	Uninit();
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage2_1Scene::Init()
{
	auto mapData = tile_map_manager_->LoadCSV("MapData/Stage2/Stage2_1.csv");
	tile_map_manager_->LoadTileMap(mapData);

	camera_ = new Camera(game_manager_);
	back_ground_ = new BackGround(game_manager_);
	hammerCursor_ = new HammerCursor(game_manager_);

	gearMaxCount_ = gearCounter_2_1;	// �萔����
	hammerMaxCount_ = hammerCounter_2_1;

	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);

	auto obj = new Player(game_manager_);
	obj->GetTransformComponent()->SetSize(100.0f, 100.0f);

	state_ = Game;

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

	game_manager_->GetPendulumManager()->SetHammerCursor(hammerCursor_);

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
	AudioManager::GetInstance()->Play(SoundLabel_StageBGM);


}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Stage2_1Scene::Update()
{
	auto& input = InputManager::GetInstance();
	switch (state_)
	{
	case Stage2_1Scene::Game:
		NumberChange();
		if (game_manager_->GetItemCount() == gearCounter_2_1)
		{
			state_ = Result;
			AudioManager::GetInstance()->Stop(SoundLabel_StageBGM);
		}
		// �|�[�Y��ʂɈړ�
		if (input.GetKeyTrigger(VK_P))
		{
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Paused);	// �ғ��R���e�i�̃I�u�W�F�N�g��S�ă|�[�Y��Ԃ�
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			}
			pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			state_ = Pouse;
		}
		break;
	case Stage2_1Scene::Result:
		game_manager_->ChangeScene(SceneName::Result);
		break;
	case Stage2_1Scene::Pouse:
		// �����Ƀ|�[�Y��ʂł̑����
		if (input.GetKeyTrigger(VK_P))
		{
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Active);	// �ғ��R���e�i�̃I�u�W�F�N�g��S�ă|�[�Y��Ԃ�
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			state_ = Game;
		}
		break;
	case Stage2_1Scene::Rewind:
		game_manager_->ResetItemCount();
		game_manager_->ChangeScene(SceneName::Stage2_1);
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage2_1Scene::Uninit()
{
}
