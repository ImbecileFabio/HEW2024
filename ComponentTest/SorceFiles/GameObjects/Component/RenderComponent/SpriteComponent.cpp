//==================================================
// [SpriteComponent.cpp] �`��R���|�[�l���g 
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�l�p��`�悷��
//==================================================
/*----- �C���N���[�h -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Direct3D.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("�s���ȃI�u�W�F�N�g");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
SpriteComponent::~SpriteComponent(void)
{
}

//--------------------------------------------------
// �I�u�W�F�N�g�̖��O���Z�b�g
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string objectName)
{
	object_name_ = objectName;
}

//--------------------------------------------------
// �`�揈��
//--------------------------------------------------
void SpriteComponent::Draw(void)
{
	std::cout << object_name_ + "�̃X�v���C�g���`�悳�ꂽ\n";
}

//==================================================
//				End of FIle
//==================================================