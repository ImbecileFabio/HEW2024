//=================================================================
// [Effect.cpp] Effect�\�[�X�t�@�C��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����FEffect�ł�
// �܂��G���Ă���r���ł�
//=================================================================

/*----- �C���N���[�h -----*/
#include "Effect.h"

#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
Effect::Effect(GameManager* _gameManager, GameObject* _owner, const std::string& _effectTex)
	:GameObject(_gameManager, "Effect")
	, is_finish_(false)
	, owner_(_owner)
{

	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);
	transform_component_->SetPosition(owner_->GetTransformComponent()->GetPosition());


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
	// �A�j���[�V�������I���I���t���O���I����
	if (!animation_component_->GetIsPlaying())
	{
		//is_finish_ = true;
		delete this;
	}
}

