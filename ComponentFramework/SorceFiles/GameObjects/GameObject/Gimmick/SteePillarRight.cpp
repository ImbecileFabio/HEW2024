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
#include "../../Component/RenderComponent/AnimationComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../Component/GravityComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarRight::SteePillarRight(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRight")
	, sprite_component_(nullptr)
	, animation_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarRight::~SteePillarRight(void)
{
	delete sprite_component_;
	delete animation_component_;
	delete gravity_component_;
	delete velocity_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarRight::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal", 1);
	animation_component_ = new AnimationComponent(this, sprite_component_);
	velocity_component_ = new VelocityComponent(this);
	gravity_component_ = new GravityComponent(this);
	gravity_component_->SetGravity(-1.2f);
	gravity_component_->SetIsRobot(false);
	gravity_component_->SetUseGravityFlg(false);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarRight::UpdateGameObject(void)
{
	if (isDown_)
	{
		gravity_component_->SetUseGravityFlg(true);
	}
	else
	{
		//auto pos = transform_component_->GetPosition();
		//transform_component_->SetPosition()
	}

	// ����Velocity�������Ă�����
	if (isFloorVelocityStop_)
	{
		// ���̈ʒu���擾
		auto floorPos = floorPosition_;
		Vector3 pos = transform_component_->GetPosition();

		// ���Ƃ̍������I�t�Z�b�g�Ƃ��Đݒ�
		offset_ = Vector3(floorPos.x - pos.x, floorPos.y - pos.y, 0.0f);

		// �ʒu���I�t�Z�b�g��K�p���čX�V
		transform_component_->SetPositionY(pos.y + offset_.y);
	}
	else
	{

	}

}
//--------------------------------------------------
// @brief ���L�����O���[�v�̎Q�Ƃ�ݒ�
// @param _group[�S���O���[�v]
//--------------------------------------------------
void SteePillarRight::SetPillarRightGroup(SteePillarRightGroup* _group)
{
	stee_pillar_right_group_ = _group;
}

