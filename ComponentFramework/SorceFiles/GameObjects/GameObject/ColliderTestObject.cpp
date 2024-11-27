//==================================================
// [ColliderTestObject.cpp] �����蔻��e�X�g�p�I�u�W�F�N�g��CPP�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻����������e�X�g�p�I�u�W�F�N�g�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "ColliderTestObject.h"
#include "../../InputManager.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/ColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#define TEXTURE_PATH "Asset/Texture/"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("{}\n", "��ColliderTestObject�� -> Constructor");

	// �X�v���C�g�R���|�[�l���g
	this->sprite_component_ = new SpriteComponent(this, TEXTURE_PATH "TestBlock.png");

	// �l�p�����蔻��R���|�[�l���g
	this->circle_collider_component_ = new CircleColliderComponent(this);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
ColliderTestObject::~ColliderTestObject(void)
{
	delete sprite_component_;
	delete circle_collider_component_;
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void ColliderTestObject::UpdateGameObject(void)
{
	if (circle_collider_component_->testFg)
	{
		//transform_component_->position_.x = 100.0f;
	}
}
