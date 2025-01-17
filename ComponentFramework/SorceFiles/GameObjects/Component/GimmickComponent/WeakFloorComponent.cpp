//==================================================
// [WeakFloorComponent.cpp] �Ƃ����M�~�b�N�R���|�[�l���g�\�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Ƃ����M�~�b�N�R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
#include "WeakFloorComponent.h"
#include "../../GameObject.h"
#include "../ColliderComponent/BoxColliderComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../RenderComponent/SpriteComponent.h"
#include "../RenderComponent.h"
#include "../GravityComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloorComponent::WeakFloorComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
WeakFloorComponent::~WeakFloorComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void WeakFloorComponent::Init()
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_sprite_ = owner_->GetComponent<RenderComponent>();
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void WeakFloorComponent::Uninit()
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void WeakFloorComponent::Update()
{
	if (!owner_transform_ || !owner_collider_ || !owner_sprite_)
	{
		std::cout << std::format("��WeakFloorComponent�� -> Update Error\n");
		return;
	}
}
//--------------------------------------------------
// @brief �摜��`�悵�Ȃ��悤�ɕς���
//--------------------------------------------------
void WeakFloorComponent::NotSpriteDraw(void)
{
	owner_sprite_->SetState(RenderComponent::State::notDraw);
}
