//=================================================================
// [SteePillarLeftGroup.cpp] SteePillarLeftGroup�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����FSteePillarLeftGroup����
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarLeftGroup.h"
#include "../SteePillarLeft.h"
#include "../../../Component/TimerComponent.h"
#include "../../../Component/RenderComponent/AnimationComponent.h"
#include "../../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../../Component/GravityComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarLeftGroup::SteePillarLeftGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeftGroup")
	, isStart_		 (false)
	, isBreak_		 (false)
	, isBreakStop_	 (false)
	, isBreakStart_	 (false)
	, isDownStart_	 (false)
	, isAnimationEnd_(false)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarLeftGroup::~SteePillarLeftGroup(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarLeftGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarLeftGroup::UpdateGameObject(void)
{
	if (!isStart_)
	{
		steePillarLeftTiles_[0]->SetObjectName("SteelPillar_Top_Left");
		owner_top_animation_component_ = steePillarLeftTiles_[0]->GetComponent<AnimationComponent>();
		owner_top_sprite_component_	   = steePillarLeftTiles_[0]->GetComponent<SpriteComponent>();
		isStart_ = true;
	}
	// �򉻏�Ԃɐ؂�ւ��i���̂݁j
	if (isBreak_ && !isBreakStart_)
	{
		if (!isTopChangeTile_)
		{
			owner_top_sprite_component_->SetTexture("steelpillar_pillar_break");
		}
		owner_top_animation_component_->PlayAnimation();
		isBreak_	  = false;
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
		steePillarLeftTiles_[1]->GetComponent<SpriteComponent>()->SetTexture("steelpillar_pillar_bottom");
		isAnimationEnd_ = true;
		isBreakStart_ = false;
		isDownStart_ = true;
	}
	// �����������J�n
	if (isDownStart_)
	{
		for (int i = 1; i < steePillarLeftTiles_.size(); ++i)
		{
			auto steePillarTile = dynamic_cast<SteePillarLeft*>(steePillarLeftTiles_[i]);
			if (!steePillarTile->GetIsDown())
			{
				steePillarTile->SetIsDown(true);
			}
		}
		auto steePillarTile = dynamic_cast<SteePillarLeft*>(steePillarLeftTiles_[0]);
		steePillarTile->GetComponent<SpriteComponent>()->SetTexture("steelpillar_pillar_top");
		isDownStart_ = false;
		isTopChangeTile_ = true;
	}
}
//--------------------------------------------------
// @brief �^�C���̑��x���~
//--------------------------------------------------
void SteePillarLeftGroup::SetVelocityStop()
{
	for (auto& it : steePillarLeftTiles_)
	{
		it->GetComponent<GravityComponent>()->SetGravity(false);
		it->GetComponent<VelocityComponent>()->ResetVelocity();
	}
}
//--------------------------------------------------
// @brief ���S���^�C����ǉ�
// @param _tile[�ǉ�����^�C���I�u�W�F�N�g]
//--------------------------------------------------
void SteePillarLeftGroup::AddSteePillarLeftTile(GameObject* _tile)
{
	steePillarLeftTiles_.emplace_back(_tile);
	auto steePillar = dynamic_cast<SteePillarLeft*>(_tile);
	steePillar->SetPillarLeftGroup(this);
}
