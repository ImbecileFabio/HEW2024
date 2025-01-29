//==================================================
// [SceneBase.cpp] �V�[���x�[�X�N���X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�V�[���̊��N���X
//==================================================

/*----- �C���N���[�h -----*/
#include <memory>
#include "SceneBase.h"

#include "../GameObjects/GameObject/Revolution.h"
#include "../GameManager.h"
#include "../TileMapManager.h"
#include "../InputManager.h"
#include "../PemdulumManager.h"
#include "../AudioManager.h"
//--------------------------------------------------
// @param	_gameManager �V�[���̏��L��, _sceneName �V�[����
// @brief	�R���X�g���N�^
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// ���L��
	, scene_name_(_sceneName)		// �V�[����
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
	tile_map_manager_ = std::make_unique<TileMapManager>(game_manager_);

	stageUIs_[0] = new Revolution(game_manager_, "stageUI", "stageUI",2);
	stageUIs_[0]->GetTransformComponent()->SetSize(512.0f, 512.0f);
	stageUIs_[0]->GetTransformComponent()->SetPosition(-702.0f, 365.0f);
	stageUIs_[1] = new Revolution(game_manager_, "pause_button", "pause_button", 2);
	stageUIs_[1]->GetTransformComponent()->SetSize(128.0f, 128.0f);
	stageUIs_[1]->GetTransformComponent()->SetPosition(861.0f, 445.0f);

	gearMax_ = new Revolution(game_manager_, "numbers", "gearMax");
	gearMax_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearMax_->GetTransformComponent()->SetPosition(-551.0f, 412.0f);
	gearMax_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	gearGet_ = new Revolution(game_manager_, "numbers", "gearGet");
	gearGet_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	gearGet_->GetTransformComponent()->SetPosition(-677.0f, 454.0f);
	gearGet_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	hammerNum_ = new Revolution(game_manager_, "numbers", "hammerNum");
	hammerNum_->GetTransformComponent()->SetPosition(-596.0f, 290.0f);
	hammerNum_->GetTransformComponent()->SetSize(100.0f, 100.0f);
	hammerNum_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);

	pauseWindow_ = new Revolution(game_manager_, "pose_window", "pose_window");
	pauseWindow_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pauseWindow_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pause_instruction_ = new Revolution(game_manager_, "instruction_window", "instruction_window", 51);
	pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	pause_instruction_->GetTransformComponent()->SetSize(1980.0f, 1080.0f);

	pauseButtons_[0] = new Revolution(game_manager_, "pose_return_game","pose_return_game");
	pauseButtons_[1] = new Revolution(game_manager_, "pose_restart", "pose_restart");
	pauseButtons_[2] = new Revolution(game_manager_, "pose_select", "pose_select");
	pauseButtons_[3] = new Revolution(game_manager_, "pose_instruction", "pose_instruction");
	pauseButtons_[4] = new Revolution(game_manager_, "pose_option", "pose_option");
	pauseButtons_[0]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[0]->GetTransformComponent()->SetPosition(0.0f, 365.0f);
	pauseButtons_[1]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[1]->GetTransformComponent()->SetPosition(0.0f, 200.0f);
	pauseButtons_[2]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[2]->GetTransformComponent()->SetPosition(0.0f, 35.0f);
	pauseButtons_[3]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[3]->GetTransformComponent()->SetPosition(0.0f, -130.0f);
	pauseButtons_[4]->GetTransformComponent()->SetSize(900.0f, 900.0f);
	pauseButtons_[4]->GetTransformComponent()->SetPosition(0.0f, -295.0f);
	for(auto& it : pauseButtons_)
		it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
}

SceneBase::~SceneBase()
{
	std::cout << std::format("[{}] -> Destructor\n", scene_name_);
}

void SceneBase::PauseWindow()
{
	// �����ő�����L�q
	auto& input = InputManager::GetInstance();
	// �E�B���h�E���X�ɊJ���Ă��Ȃ��Ƃ������{�^����������s
	if (!isWindowOpen)
	{
		if (input.GetKeyTrigger(VK_UP))				// �㉺�ړ�
			pause_select_button_--;
		if (input.GetKeyTrigger(VK_DOWN))
			pause_select_button_++;
		if (pause_select_button_ > 4)				// �܂�Ԃ�����
			pause_select_button_ = 0;
		if (pause_select_button_ < 0)
			pause_select_button_ = 4;
	}
	else
	{
		if (input.GetKeyTrigger(VK_X))
		{
			if (pause_select_button_ == 3) 
			{
				isWindowOpen = false;
				pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			if (pause_select_button_ == 4)
			{
				isWindowOpen = false;
			}
		}
	}
	// �I�𒆂̃{�^���ɐF�̕ω������鏈��
	for (int i = 0; i < pauseButtons_.size(); ++i)
	{
		if (i == pause_select_button_)
		{
			// �I�𒆂̃{�^���̐F��ύX
			pauseButtons_[i]->GetComponent<SpriteComponent>()->SetColor({ 0.5f, 0.5f, 1.0f, 1.0f });
		}
		else
		{
			// ���I���̃{�^���̐F�����ɖ߂�
			pauseButtons_[i]->GetComponent<SpriteComponent>()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	// ���ݑI������Ă���Y�����ɂ���Č��菈����ύX
	if (input.GetKeyTrigger(VK_RETURN))
	{
		switch (pause_select_button_)
		{
		case 0:	// �Q�[����ʂɖ߂�
			stageState_ = StageState::Game;
			for (auto& it : game_manager_->GetGameObjects())
			{
				it->SetState(GameObject::State::Active);	// �ғ��R���e�i�̃I�u�W�F�N�g��S�ŉғ���Ԃ�
			}
			for (auto& it : pauseButtons_)
			{
				it->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
			pauseWindow_	  ->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			break;
		case 1:	// ���X�^�[�g
			stageState_ = StageState::Rewind;
			break;
		case 2:	// �Z���N�g��ʂɖ߂�
			game_manager_->ResetItemCount();
			game_manager_->ChangeScene(SceneName::Title);
			AudioManager::GetInstance()->Stop(SoundLabel_StageBGM);
			break;
		case 3:	// ���������\��
			pause_instruction_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			isWindowOpen = true;
			break;
		case 4:	// �I�v�V�����E�B���h�E��\��
			OptionWindow();
			isWindowOpen = true;
			break;
		default:
			break;
		}
	}
}

void SceneBase::OptionWindow()
{

}

void SceneBase::NumberChange()
{
	// �M�A��MAX����\��
	auto gearSpriteComponent = gearMax_->GetComponent<SpriteComponent>();
	// �M�A�̎擾��Ԃ�\��
	auto gearGetSpriteComponent = gearGet_->GetComponent<SpriteComponent>();
	// �n���}�[�̒@����񐔂�\��
	auto hammerSpriteComponent = hammerNum_->GetComponent<SpriteComponent>();
	// �M�A��MAX���ɂ����UV��ύX
	DirectX::SimpleMath::Vector2 frameSize = gearSpriteComponent->GetTexture().get()->GetFrameSize();
	gearSpriteComponent->SetUV({ gearMaxCount_ * frameSize.x, 0.0f * frameSize.y });
	gearGetSpriteComponent->SetUV({ game_manager_->GetItemCount() * frameSize.x, 0.0f * frameSize.y });
	// �n���}�[�̒@����񐔂ɂ����UV��ύX
	switch (hammerMaxCount_)
	{
	case 0:
		hammerSpriteComponent->SetUV({ 0.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 1:
		hammerSpriteComponent->SetUV({ 1.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 2:
		hammerSpriteComponent->SetUV({ 2.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 3:
		hammerSpriteComponent->SetUV({ 3.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 4:
		hammerSpriteComponent->SetUV({ 4.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	case 5:
		hammerSpriteComponent->SetUV({ 5.0f * frameSize.x, 0.0f * frameSize.y});
		break;
	}
	if (hammerMaxCount_ == 0)
	{
		isHammerMax_ = true;
	}
}

