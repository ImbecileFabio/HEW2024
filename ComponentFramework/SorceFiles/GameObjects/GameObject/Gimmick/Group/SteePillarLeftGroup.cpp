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
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarLeftGroup::SteePillarLeftGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeftGroup")
	, timer_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SteePillarLeftGroup::~SteePillarLeftGroup(void)
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarLeftGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarLeftGroup::UpdateGameObject(void)
{
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
