//=================================================================
// [Effect.cpp] Effect�\�[�X�t�@�C��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����FEffect�ł�
// �܂��G���Ă���r���ł�
//=================================================================

/*----- �C���N���[�h -----*/
#include "Effect.h"

#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/TimerComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
Effect::Effect(GameManager* _gameManager, const std::string& _effectTex)
	:GameObject(_gameManager, "Effect")
{
	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);

	auto texture = sprite_component_->GetTexture();
	auto triggerTime = texture->GetAnmSpeed() * texture->GetCutU() * texture->GetCutV();	// ���t���[�������擾����֐��ɕύX�\��

	timer_component_ = new TimerComponent(this, triggerTime);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Effect::~Effect(void)
{

}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Effect::InitGameObject(void)
{

}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Effect::UpdateGameObject(void)
{

}

