#include "Stage1_4Scene.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../../PemdulumManager.h"
#include "../../InputManager.h"
#include "../../TileMapManager.h"
#include "../../AudioManager.h"

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


constexpr int gearCounter_1_4 = 2;		// �M�A�̊l����
constexpr int hammerCounter_1_4 = 2;	// �@������
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Stage1_4Scene::Stage1_4Scene(GameManager* _gameManager)
	:SceneBase(_gameManager, "Stage1_4")
{
	Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Stage1_4Scene::~Stage1_4Scene()
{
	Uninit();
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Stage1_4Scene::Init()
{
	auto mapData = tile_map_manager_->LoadCSV("MapData/Stage1/Stage1_4.csv");
	tile_map_manager_->LoadTileMap(mapData);

	camera_ = new Camera(game_manager_);
	back_ground_ = new BackGround(game_manager_);
	hammerCursor_ = new HammerCursor(game_manager_);

	gearMaxCount_ = gearCounter_1_4;	// �萔����
	hammerMaxCount_ = hammerCounter_1_4;

	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);

	stageState_ = Game;

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
void Stage1_4Scene::Update()
{
	auto& input = InputManager::GetInstance();
	if (input.GetKeyTrigger(VK_R))
		stageState_ = StageState::Rewind;
	switch (stageState_)
	{
	case Stage1_4Scene::Game:
		NumberChange();
		if (game_manager_->GetItemCount() == gearCounter_1_4)
		{
			stageState_ = Result;
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
			stageState_ = Pouse;
		}
		break;
	case Stage1_4Scene::Result:
		game_manager_->TransitionToScene(SceneName::Result);
		break;
	case Stage1_4Scene::Pouse:
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
			stageState_ = Game;
		}
		break;
	case Stage1_4Scene::Rewind:
		game_manager_->ResetItemCount();
		game_manager_->TransitionToScene(SceneName::Stage1_4);
		break;
	default:
		break;
	}

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void Stage1_4Scene::Uninit()
{
}
