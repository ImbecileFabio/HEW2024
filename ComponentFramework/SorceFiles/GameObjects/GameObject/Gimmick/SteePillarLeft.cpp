//=================================================================
// [SteePillarLeft.cpp] �S���I�u�W�F�N�g��CPP
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���I�u�W�F�N�g�̎���
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarLeft.h"
#include "../Gimmick/Group/SteePillarLeftGroup.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../Component/GravityComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarLeft::SteePillarLeft(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeft")
	, sprite_component_(nullptr)
	, animation_component_(nullptr)
	, offset_(0.0f, 0.0f)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarLeft::~SteePillarLeft(void)
{
	delete sprite_component_;
	delete animation_component_;
	delete gravity_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarLeft::InitGameObject(void)
{
	offset_ = {11.0f, 0.0f };
	sprite_component_	 = new SpriteComponent(this, "steelpillar_pillar_normal", 1);
	animation_component_ = new AnimationComponent(this, sprite_component_);
	velocity_component_	 = new VelocityComponent(this);
	gravity_component_	 = new GravityComponent(this);
	gravity_component_->SetGravity(-1.2f);
	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarLeft::UpdateGameObject(void)
{
	if (!offsetFg_)
	{
		Vector3 pos = transform_component_->GetPosition();
		transform_component_->SetPosition(pos.x - offset_.x, pos.y + offset_.y);
		offsetFg_ = true;
	}
	if (isDown_)
	{
		gravity_component_->SetUseGravityFlg(true);
	}
}
//--------------------------------------------------
// @brief ���S���O���[�v�̎Q�Ƃ�ݒ�
// @param _group[���S���O���[�v]
//--------------------------------------------------
void SteePillarLeft::SetPillarLeftGroup(SteePillarLeftGroup* _group)
{
	stee_pillar_left_group_ = _group;
}

