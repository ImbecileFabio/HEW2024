#include "TimeZoneComponent.h"
#include "../../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../Component/RigidbodyComponent.h"
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
	this->colliderComponent_ = this->owner_->GetComponent<ColliderBaseComponent>();	
	this->rigidbodyComponent_ = this->owner_->GetComponent<RigidbodyComponent>();
}
//--------------------------------------------------
// @brief �^�C���]�[���̏I������
//--------------------------------------------------
void TimeZoneComponent::Uninit(void)
{
	delete this->colliderComponent_;
	delete this->rigidbodyComponent_;
}
//--------------------------------------------------
// @brief �^�C���]�[���̍X�V����
//--------------------------------------------------
void TimeZoneComponent::Update(void)
{
}
