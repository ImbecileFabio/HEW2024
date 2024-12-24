#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/PendulumMovementComponent.h"
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
	delete pendulum_component_;
}
//--------------------------------------------------
// @brief �U��q�̖_�̏���������
//--------------------------------------------------
void Stick::InitGameObject(void)
{
	sprite_component_	= new SpriteComponent(this, TEXTURE_PATH_"huriko/v02/stick_01.png");
	transform_component_->SetSize(100.0f, 300.0f);
}
//--------------------------------------------------
// @brief �U��q�̖_�̍X�V����
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
}
