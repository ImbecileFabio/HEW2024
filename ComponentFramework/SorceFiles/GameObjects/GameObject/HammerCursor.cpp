//=================================================================
// [HammerCursor.cpp] �U��q��I������J�[�\���\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�U��q��I������J�[�\���̊ȒP�ȋ@�\������
//=================================================================
/*----- �C���N���[�h -----*/
#include "HammerCursor.h"
#include "../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
HammerCursor::HammerCursor(GameManager* _gameManager)
	:GameObject(_gameManager, "HammerCursor")
	, sprite_component_		(nullptr)
	, hit_effect_component_	(nullptr)
	, animation_component_	(nullptr)
	, direction_(1)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
HammerCursor::~HammerCursor(void)
{
	delete sprite_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void HammerCursor::InitGameObject(void)
{
	isUiDraw_ = true;
	sprite_component_	  = new SpriteComponent(this, "hammer", 3);
	transform_component_->SetSize(50.0f, 50.0f);
	transform_component_->SetRotation(-13.0f);
	transform_component_->SetPosition(-2000.0f, 0.0f);
	offset_ = { 45.0f, -10.0f };
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void HammerCursor::UpdateGameObject(void)
{
	// �`��؂�ւ�
	if (isUiDraw_)
		sprite_component_->SetState(RenderComponent::State::draw);
	else
		sprite_component_->SetState(RenderComponent::State::notDraw);

}
void HammerCursor::HammerCursorMove()
{
	if (direction_ == -1)
	{
		transform_component_->SetRotation(-13.0f);
		origin_pos_ += offset_;
	}
	else if (direction_ == 1)
	{
		transform_component_->SetRotation(-12.0f);
		origin_pos_.x -= offset_.x;
		origin_pos_.y += offset_.y;
	}
	transform_component_->SetPosition(origin_pos_);
}