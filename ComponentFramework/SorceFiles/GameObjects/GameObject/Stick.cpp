#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// @brief �U��q�̖_�̃R���X�g���N�^
//--------------------------------------------------
Stick::Stick(GameManager* _gameManager)
	:GameObject(_gameManager, "Stick")
{
	InitGameObject();
}
//--------------------------------------------------
// @brief �U��q�̖_�̃f�X�g���N�^
//--------------------------------------------------
Stick::~Stick()
{
	delete sprite_component_;
	delete stick_move_component_;
}
//--------------------------------------------------
// @brief �U��q�̖_�̏���������
//--------------------------------------------------
void Stick::InitGameObject(void)
{
	stick_move_component_ = new StickMoveComponent(this);
	sprite_component_	= new SpriteComponent(this, "stick", 9);
	transform_component_->SetSize(50.0f, 200.0f);
}
//--------------------------------------------------
// @brief �U��q�̖_�̍X�V����
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
}
