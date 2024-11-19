//==================================================
// [Pendulum.cpp] �U��q�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Pendulum.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("��Pendulum�� -> Constructor\n");

	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, "Asset/Texture/HEW���f��/Ball.png");
	sprite_component_->SetObjectName("Pendulum");

	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumComponent(this);

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	std::cout << std::format("��Pendulum�� -> Destructor\n");
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete pendulum_component_;
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	GetAsyncKeyState(VK_UP);
}
