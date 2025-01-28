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
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarLeftGroup::SteePillarLeftGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeftGroup")
	, timer_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarLeftGroup::~SteePillarLeftGroup(void)
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarLeftGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarLeftGroup::UpdateGameObject(void)
{
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
