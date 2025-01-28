#include "SteePillarRightGroup.h"
#include "../SteePillarRight.h"
#include "../../../Component/TimerComponent.h"
#include "../../../Component/RenderComponent/AnimationComponent.h"
#include "../../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../../Component/GravityComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarRightGroup::SteePillarRightGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRightGroup")
	, isStart_(false)
	, isBreak_(false)
	, isBreakStop_(false)
	, isBreakStart_(false)
	, isDownStart_(false)
	, isAnimationEnd_(false)
{
	InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarRightGroup::~SteePillarRightGroup()
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarRightGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarRightGroup::UpdateGameObject(void)
{
	// ����������
	if (!isStart_)
	{
		steePillarRightTiles_[0]->SetObjectName("SteelPillar_Top_Right");
		owner_top_animation_component_ = steePillarRightTiles_[0]->GetComponent<AnimationComponent>();
		owner_top_sprite_component_ = steePillarRightTiles_[0]->GetComponent<SpriteComponent>();
		isStart_ = true;
	}
	// �򉻏�Ԃɐ؂�ւ��i���̂݁j
	if (isBreak_ && !isBreakStart_)
	{
		owner_top_sprite_component_->SetTexture("steelpillar_pillar_break");
		owner_top_animation_component_->PlayAnimation();
		isBreak_ = false;
		isBreakStart_ = true;
		return;
	}
	// �A�j�����~�߂�
	if (isBreakStop_ && isBreakStart_)
	{
		owner_top_animation_component_->StopAnimation();
		isBreakStart_ = false;
	}
	// �A�j���[�V��������~�����炩�򉻂��n�܂��Ă�����
	if (!owner_top_animation_component_->GetIsPlaying() && isBreakStart_ && !isBreakStop_ && !isDownStart_)
	{
		isAnimationEnd_ = true;
		isBreakStart_ = false;
		isDownStart_ = true;
	}
	// �����������J�n
	if (isDownStart_)
	{
		for (int i = 1; i < steePillarRightTiles_.size(); ++i)
		{
			auto steePillarTile = dynamic_cast<SteePillarRight*>(steePillarRightTiles_[i]);
			if (!steePillarTile->GetIsDown())
			{
				steePillarTile->SetIsDown(true);
			}
		}
		auto steePillarTile = dynamic_cast<SteePillarRight*>(steePillarRightTiles_[0]);
		steePillarTile->GetComponent<SpriteComponent>()->SetTexture("steelpillar_pillar_top");
		isDownStart_ = false;
	}
}
//--------------------------------------------------
// @brief �^�C�����~�����鏈��
//--------------------------------------------------
void SteePillarRightGroup::SetVelocityStop()
{
	for (auto& tile : steePillarRightTiles_)
	{
		tile->GetComponent<GravityComponent>()->SetGravity(false);
		tile->GetComponent<VelocityComponent>()->ResetVelocity();
	}
}
//--------------------------------------------------
// @brief �^�C����ǉ����鏈��
//--------------------------------------------------
void SteePillarRightGroup::AddSteePillarRightTile(GameObject* _tile)
{
	steePillarRightTiles_.emplace_back(_tile);
	auto steePillar = dynamic_cast<SteePillarRight*>(_tile);
	steePillar->SetPillarRightGroup(this);
}
