//=================================================================
// [SteePillarLeftTop.cpp] �S���I�u�W�F�N�g�̈�ԏ�
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���I�u�W�F�N�g�̈�ԏ����
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarLeftTop.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarLeftTop::SteePillarLeftTop(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarLeftTop")
	, sprite_component_(nullptr)
	, animation_component_(nullptr)
	, offsetFg_(false)
	, offset_(0.0f, 0.0f)
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarLeftTop::~SteePillarLeftTop(void)
{
	delete sprite_component_;
	delete animation_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarLeftTop::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
	//animation_component_ = new AnimationComponent(this, sprite_component_);
	offset_ = { 11.0f, 0.0f };
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarLeftTop::UpdateGameObject(void)
{
	if (!offsetFg_)
	{
		Vector3 pos = transform_component_->GetPosition();
		transform_component_->SetPosition(pos.x - offset_.x, pos.y + offset_.y);
		offsetFg_ = true;
	}
}

