//=================================================================
// [SteePillarFloor.cpp] �S���I�u�W�F�N�g��CPP
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���I�u�W�F�N�g�̎���
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarFloor.h"
#include "../../../TileMapManager.h"
#include "../Gimmick/Group/SteePillarFloorGroup.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GravityComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarFloor::SteePillarFloor(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillar")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarFloor::~SteePillarFloor(void)
{
	delete sprite_component_;
	delete gravity_component_;
	delete box_collider_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarFloor::InitGameObject(void)
{
	sprite_component_		= new SpriteComponent(this, "steelpillar_floor_center");
	gravity_component_		= new GravityComponent(this);
	box_collider_component_ = new BoxColliderComponent(this);
	velocity_component_		= new VelocityComponent(this);
	//transform_component_->SetSize(TILE_SIZE_X * 1.5f, TILE_SIZE_Y * 1.5f);
	box_collider_component_->SetSize(transform_component_->GetSize().x, transform_component_->GetSize().y * 0.2f);

}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarFloor::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief �O���[�v�̎Q�Ƃ�ݒ�
// @param _stee_pillar_floor_group[�S���̑���O���[�v]
//--------------------------------------------------
void SteePillarFloor::SetSteePillarFloorGroup(SteePillarFloorGroup* _stee_pillar_floor_group)
{
	stee_pillar_floor_group_ = _stee_pillar_floor_group;
}

