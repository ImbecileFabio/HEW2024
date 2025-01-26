//=================================================================
// [SteePillarRightTop.cpp] �E�S���I�u�W�F�N�g�̈�ԏ�
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�E�S���I�u�W�F�N�g�̈�ԏ����
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarRightTop.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarRightTop::SteePillarRightTop(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarRightTop")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SteePillarRightTop::~SteePillarRightTop(void)
{
	delete sprite_component_;
	delete animation_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarRightTop::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "steelpillar_pillar_normal");
	//animation_component_ = new AnimationComponent(this, sprite_component_);
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarRightTop::UpdateGameObject(void)
{

}

