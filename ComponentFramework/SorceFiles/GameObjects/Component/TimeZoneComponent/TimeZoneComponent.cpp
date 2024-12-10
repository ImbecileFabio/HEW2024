#include "TimeZoneComponent.h"
#include "../../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief �^�C���]�[���̃R���X�g���N�^
//--------------------------------------------------
TimeZoneComponent::TimeZoneComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief �^�C���]�[���̃f�X�g���N�^
//--------------------------------------------------
TimeZoneComponent::~TimeZoneComponent()
{
	this->Uninit();
}
//--------------------------------------------------
// @brief �^�C���]�[���̏�����
//--------------------------------------------------
void TimeZoneComponent::Init(void)
{	// �I�u�W�F�N�g�̃R���C�_�[���Q�ƂŎ���
	this->collider_component_ = this->owner_->GetComponent<ColliderBaseComponent>();	
	this->velocity_component_ = this->owner_->GetComponent<VelocityComponent>();
}
//--------------------------------------------------
// @brief �^�C���]�[���̏I������
//--------------------------------------------------
void TimeZoneComponent::Uninit(void)
{
	delete this->collider_component_;
	delete this->velocity_component_;
}
//--------------------------------------------------
// @brief �^�C���]�[���̍X�V����
//--------------------------------------------------
void TimeZoneComponent::Update(void)
{
}
