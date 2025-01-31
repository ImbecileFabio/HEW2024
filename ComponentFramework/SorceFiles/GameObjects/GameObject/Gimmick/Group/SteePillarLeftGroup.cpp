//=================================================================
// [SteePillarLeftGroup.cpp] SteePillarLeftGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：SteePillarLeftGroup実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarLeftGroup.h"
#include "../SteePillarLeft.h"
#include "../../../Component/TimerComponent.h"
#include "../../../Component/RenderComponent/AnimationComponent.h"
#include "../../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../../Component/GravityComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
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
// @brief デストラクタ
//--------------------------------------------------
SteePillarLeftGroup::~SteePillarLeftGroup(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarLeftGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief 更新処理
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
	// 劣化状態に切り替え（一回のみ）
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
	// アニメを止める
	if (isBreakStop_ && isBreakStart_)
	{
		owner_top_animation_component_->StopAnimation();
		isBreakStart_ = false;
	}
	// アニメーションが停止したらかつ劣化が始まっていたら
	if (!owner_top_animation_component_->GetIsPlaying() && isBreakStart_ && !isBreakStop_ && !isDownStart_)
	{
		steePillarLeftTiles_[1]->GetComponent<SpriteComponent>()->SetTexture("steelpillar_pillar_bottom");
		isAnimationEnd_ = true;
		isBreakStart_ = false;
		isDownStart_ = true;
	}
	// 落下処理を開始
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
// @brief タイルの速度を停止
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
// @brief 左鉄柱タイルを追加
// @param _tile[追加するタイルオブジェクト]
//--------------------------------------------------
void SteePillarLeftGroup::AddSteePillarLeftTile(GameObject* _tile)
{
	steePillarLeftTiles_.emplace_back(_tile);
	auto steePillar = dynamic_cast<SteePillarLeft*>(_tile);
	steePillar->SetPillarLeftGroup(this);
}
