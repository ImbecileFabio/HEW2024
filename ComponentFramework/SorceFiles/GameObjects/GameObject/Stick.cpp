#include "Stick.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// @brief �U��q�̖_�̃R���X�g���N�^
//--------------------------------------------------
Stick::Stick(GameManager* _gameManager, Pendulum* _pendulum)
	:GameObject(_gameManager, "Stick")
	, owner_pendulum_(_pendulum)
	, stick_length_state_(StickLengthState::Short)
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
	stick_move_component_ = new StickMoveComponent(this, owner_pendulum_);
	sprite_component_	= new SpriteComponent(this, "stick", 30);
	stick_length_state_ = StickLengthState::Middle;
}
//--------------------------------------------------
// @brief �U��q�̖_�̍X�V����
//--------------------------------------------------
void Stick::UpdateGameObject(void)
{
	
	// �U��q�̋��̏�Ԃɂ����state���ς��
	switch (stick_length_state_)
	{
	case StickLengthState::Short:

		break;
	case StickLengthState::Middle:

		break;
	case StickLengthState::Long:

		break;
	}


	// �_�̏�Ԃ��R���|�[�l���g�ɔ��f����
	stick_move_component_->SetLengthState(static_cast<StickMoveComponent::LengthState>(stick_length_state_));


}
