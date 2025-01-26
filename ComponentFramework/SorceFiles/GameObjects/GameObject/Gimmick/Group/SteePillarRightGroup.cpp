#include "SteePillarRightGroup.h"
#include "../SteePillarRight.h"
#include "../../../Component/TimerComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarRightGroup::SteePillarRightGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRightGroup")
	, timer_component_(nullptr)
{
	InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SteePillarRightGroup::~SteePillarRightGroup()
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarRightGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarRightGroup::UpdateGameObject(void)
{
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
