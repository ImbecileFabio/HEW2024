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
	sprite_component_	  = new SpriteComponent(this, "hammer");
	transform_component_->SetSize(100.0f, 100.0f);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void HammerCursor::UpdateGameObject(void)
{
	// �`��؂�ւ�
	if (isUiDraw)
		sprite_component_->SetState(RenderComponent::State::draw);
	else
		sprite_component_->SetState(RenderComponent::State::notDraw);

	//origin_pos_.x = origin_pos_.x;
	transform_component_->SetPosition(origin_pos_);
	//if (!isUiDraw)						// UI����\��
	//{
	//	isUiDraw = true;
	//	isCursorMove = false;	// �J�[�\���͓������Ȃ�
	//	sprite_component_->SetState(RenderComponent::State::notDraw);
	//}
	//else if (isUiDraw && !isCursorMove)	// UI���\������Ă���ꍇ
	//{
	//	isCursorMove = true;
	//}
}