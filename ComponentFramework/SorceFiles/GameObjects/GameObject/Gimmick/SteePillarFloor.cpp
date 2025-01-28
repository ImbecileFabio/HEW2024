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
#include "../../Component/EventComponent/ColliderEventComponent.h"
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
	delete event_component_;
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
	event_component_		= new ColliderEventComponent(this);
	//transform_component_->SetSize(TILE_SIZE_X * 1.5f, TILE_SIZE_Y * 1.5f);
	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);
	box_collider_component_->SetSize(transform_component_->GetSize().x, transform_component_->GetSize().y * 0.2f);

	auto f = std::function<void(GameObject*)>(std::bind(&SteePillarFloor::OnCollisionEnter, this, std::placeholders::_1));
	event_component_->AddEvent(f);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarFloor::UpdateGameObject(void)
{
	if (isDown_)
	{
		gravity_component_->SetUseGravityFlg(true);
	}
	else
	{
		gravity_component_->SetUseGravityFlg(false);
		velocity_component_->ResetVelocity();
	}
	stee_pillar_floor_group_->UpdateSteePillarFloorTilePositions();
}
//--------------------------------------------------
// @brief �����蔻����s����
//--------------------------------------------------
void SteePillarFloor::OnCollisionEnter(GameObject* _other)
{
	if (state_ == State::Paused) return;
	if (_other->GetType() == TypeID::Tile)	// �^�C���ƓS�����^�C�����ڐG������
	{
		float posY = transform_component_->GetPosition().y;
		transform_component_->SetPositionY(posY + offsetY_);
		stee_pillar_floor_group_->SetHitTile(true);
	}
}
//--------------------------------------------------
// @brief �O���[�v�̎Q�Ƃ�ݒ�
// @param _stee_pillar_floor_group[�S���̑���O���[�v]
//--------------------------------------------------
void SteePillarFloor::SetSteePillarFloorGroup(SteePillarFloorGroup* _stee_pillar_floor_group)
{
	stee_pillar_floor_group_ = _stee_pillar_floor_group;
}

