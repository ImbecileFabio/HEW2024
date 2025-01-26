#include "SteePillarRightGroup.h"
#include "../SteePillarRight.h"
#include "../../../Component/TimerComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarRightGroup::SteePillarRightGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRightGroup")
	, timer_component_(nullptr)
{
	InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarRightGroup::~SteePillarRightGroup()
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarRightGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarRightGroup::UpdateGameObject(void)
{
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
