//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroup�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����FWeakFloorGroup����
//=================================================================
/*----- �C���N���[�h -----*/
#include "WeakFloorGroup.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void WeakFloorGroup::UpdateGameObject(void)
{
	// �O���[�v�̕��ŐƂ��^�C�����ꊇ�ŕύX��������
	for (auto& tile : weakFloorTiles_)
	{

	}
}
//--------------------------------------------------
// @brief �Ƃ����^�C����ǉ�
// @param _tile[�ǉ�����^�C���I�u�W�F�N�g]
//--------------------------------------------------
void WeakFloorGroup::AddWeakFlootTile(GameObject* _tile)
{
	weakFloorTiles_.emplace_back(_tile);
}

