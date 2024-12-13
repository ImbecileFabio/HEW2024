#include "ColliderEventComponent.h"

int ColliderEventComponent::hoge = 0;
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
	functions_.clear();
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
	for (auto& it : functions_)
	{
		it(_other);
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