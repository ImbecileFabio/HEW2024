#include "SteePillarRightGroup.h"
#include "../SteePillarRight.h"
#include "../../../Component/TimerComponent.h"
#include "../../../Component/RenderComponent/AnimationComponent.h"
#include "../../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../../Component/GravityComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
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
// @brief デストラクタ
//--------------------------------------------------
SteePillarRightGroup::~SteePillarRightGroup()
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarRightGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarRightGroup::UpdateGameObject(void)
{
	// 初期化処理
	if (!isStart_)
	{
		steePillarRightTiles_[0]->SetObjectName("SteelPillar_Top_Right");
		owner_top_animation_component_ = steePillarRightTiles_[0]->GetComponent<AnimationComponent>();
		owner_top_sprite_component_ = steePillarRightTiles_[0]->GetComponent<SpriteComponent>();
		isStart_ = true;
	}
	// 劣化状態に切り替え（一回のみ）
	if (isBreak_ && !isBreakStart_)
	{
		owner_top_sprite_component_->SetTexture("steelpillar_pillar_break");
		owner_top_animation_component_->PlayAnimation();
		isBreak_ = false;
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
		isAnimationEnd_ = true;
		isBreakStart_ = false;
		isDownStart_ = true;
	}
	// 落下処理を開始
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
// @brief タイルを停止させる処理
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
// @brief タイルを追加する処理
//--------------------------------------------------
void SteePillarRightGroup::AddSteePillarRightTile(GameObject* _tile)
{
	steePillarRightTiles_.emplace_back(_tile);
	auto steePillar = dynamic_cast<SteePillarRight*>(_tile);
	steePillar->SetPillarRightGroup(this);
}
