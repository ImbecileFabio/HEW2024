//==================================================
// [SteePillarFloorDown.cpp] �S���M�~�b�N�R���|�[�l���g�\�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�S���M�~�b�N�R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
#include "SteePillarFloorMove.h"
#include "../../../GameObject.h"
#include "../../RigidbodyComponent/VelocityComponent.h"
#include "../../GravityComponent.h"
#include "../../ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarFloorMove::SteePillarFloorMove(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarFloorMove::~SteePillarFloorMove()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarFloorMove::Init()
{
	owner_transform_	= owner_->GetTransformComponent();
	owner_velocity_		= owner_->GetComponent<VelocityComponent>();
	owner_box_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_gravity_		= owner_->GetComponent<GravityComponent>();

	direction_ = { 0.0f, -1.0f };	// �����̌����͉�����
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void SteePillarFloorMove::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarFloorMove::Update()
{
	switch (floorState_)
	{
	case SteePillarFloorMove::FloorState::Up:
		direction_ = { direction_.x, direction_.y };	// ������ɐ؂�ւ�
		owner_velocity_->SetVelocity({ 0.0f ,direction_.y * 1.0f, 0.0f });	// ������Ɉړ�
		break;
	case SteePillarFloorMove::FloorState::Stop:
		owner_velocity_->ResetVelocity();				// ��~��ԂɂȂ�����������Ȃ��ɂ���
		break;
	case SteePillarFloorMove::FloorState::Falling:		// �������
		owner_gravity_->SetUseGravityFlg(true);
		break;
	case SteePillarFloorMove::FloorState::OnLift:		// ���t�g�ƐڐG���
		// ���t�g�ƒǏ]
		break;
	case SteePillarFloorMove::FloorState::OnTile:		// �^�C���ƐڐG���
		// �^�C���ƒǏ]
		break;
	case SteePillarFloorMove::FloorState::OnLiftAndTile:// ���t�g�ƃ^�C���̓����ڐG���
		// ���t�g�ƃ^�C���ƒǏ]
		break;
	case SteePillarFloorMove::FloorState::Down:			// �������ɐ؂�ւ�
		if (owner_gravity_->CheckGroundCollision())	// �n�ʂɐڐG���Ă�����
		{
			owner_gravity_->SetUseGravityFlg(false);// �d�͂𖳌��ɂ���
			// ���ڐG���Ă���I�u�W�F�N�g�ɂ����State��ω�������

		}
		else
		{
			owner_gravity_->SetUseGravityFlg(true);	// �d�͂�L���ɂ���
		}
		//direction_ = { direction_.x, -direction_.y };	// �������ɐ؂�ւ�
		//owner_velocity_->SetVelocity({ 0.0f , direction_.y * 1.0f, 0.0f });	// �������Ɉړ�
		break;
	default:
		break;
	}
}
