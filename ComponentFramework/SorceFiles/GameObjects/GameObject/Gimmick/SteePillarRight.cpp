//=================================================================
// [SteePillarRight.cpp] �S���I�u�W�F�N�g��CPP
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���I�u�W�F�N�g�̎���
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarRight.h"
#include "Group/SteePillarRightGroup.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarRight::SteePillarRight(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRight")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarRight::~SteePillarRight(void)
{
	delete sprite_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarRight::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarRight::UpdateGameObject(void)
{

}
//--------------------------------------------------
// @brief ���L�����O���[�v�̎Q�Ƃ�ݒ�
// @param _group[�S���O���[�v]
//--------------------------------------------------
void SteePillarRight::SetPillarRightGroup(SteePillarRightGroup* _group)
{
	stee_pillar_right_group_ = _group;
}

