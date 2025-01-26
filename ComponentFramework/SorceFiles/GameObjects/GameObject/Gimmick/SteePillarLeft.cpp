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
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarLeft::SteePillarLeft(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeft")
	, sprite_component_(nullptr)
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
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarLeft::InitGameObject(void)
{
	offset_ = {11.0f, 0.0f };
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
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
}
//--------------------------------------------------
// @brief ���S���O���[�v�̎Q�Ƃ�ݒ�
// @param _group[���S���O���[�v]
//--------------------------------------------------
void SteePillarLeft::SetPillarLeftGroup(SteePillarLeftGroup* _group)
{
	stee_pillar_left_group_ = _group;
}

