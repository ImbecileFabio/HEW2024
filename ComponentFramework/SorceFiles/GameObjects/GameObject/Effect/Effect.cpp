//=================================================================
// [EffectBase.cpp] EffectBase�\�[�X�t�@�C��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����FEffectBase�ł�
// �܂��G���Ă���r���ł�
//=================================================================

/*----- �C���N���[�h -----*/
#include "EffectBase.h"

#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/TimerComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
EffectBase::EffectBase(GameManager* _gameManager, const std::string& _effectTex)
	:GameObject(_gameManager, "EffectBase")
{
	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);

	auto texture = sprite_component_->GetTexture();
	auto triggerTime = texture->GetTottalFrame() * texture->GetAnmSpeed();

	timer_component_ = new TimerComponent(this, triggerTime);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
EffectBase::~EffectBase(void)
{

}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void EffectBase::InitGameObject(void)
{

}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void EffectBase::UpdateGameObject(void)
{

}

