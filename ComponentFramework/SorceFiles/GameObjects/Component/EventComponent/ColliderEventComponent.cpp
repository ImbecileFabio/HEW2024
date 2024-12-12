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
//void ColliderEventComponent::Update(GameObject* _other)
//{
//
//}
//--------------------------------------------------
// @brief �C�x���g�̏I������
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
}
void ColliderEventComponent::AllUpdate(GameObject* _other)
{
	for (int idx = 0; idx < functions_.size(); idx++)
	{
		functions_.at(idx)(_other);
	}
}
//--------------------------------------------------
// @brief �C�x���g�̒ǉ�����
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* _other)> _event)
{
	this->functions_.emplace_back(_event);

	std::cout << std::format("��ColliderEventComponent�� -> �C�x���g�ǉ��H\n");
}