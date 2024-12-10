#include "ColliderEventComponent.h"
//--------------------------------------------------
// @brief �C�x���g�̃R���X�g���N�^
//--------------------------------------------------
ColliderEventComponent::ColliderEventComponent(GameObject* _owner, int _updateOrder)
	:EventBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief �C�x���g�̃f�X�g���N�^
//--------------------------------------------------
ColliderEventComponent::~ColliderEventComponent()
{
}
//--------------------------------------------------
// @brief �C�x���g�̏���������
//--------------------------------------------------
void ColliderEventComponent::Init(void)
{
}
//--------------------------------------------------
// @brief �C�x���g�̍X�V����
//--------------------------------------------------
void ColliderEventComponent::Update(void)
{
}
//--------------------------------------------------
// @brief �C�x���g�̏I������
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief �C�x���g�̒ǉ�����
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* collidedObject)> _event)
{
	this->functions_.emplace_back(_event);
}