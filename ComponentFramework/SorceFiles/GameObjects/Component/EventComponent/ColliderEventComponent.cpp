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
	functions_.clear();
}
//--------------------------------------------------
// @brief �C�x���g�̏I������
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
	for (auto& func : functions_)
	{
		func.second = nullptr;
	}
}
//--------------------------------------------------
// @brief �ǉ����ꂽ�C�x���g�̎��s����
// @param _other �����蔻������I�u�W�F�N�g
//--------------------------------------------------
void ColliderEventComponent::AllUpdate(GameObject* _other, size_t _id)
{

	auto it = functions_.find(_id);
	if (it != functions_.end()) 
	{
		it->second(_other);  // �֐����Ăяo��
	}
	else {
	}

}
//--------------------------------------------------
// @brief �C�x���g�̒ǉ�����
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* _other)>&_event)
{
	generalId_++;
	id_ = generalId_;
	this->functions_[id_] = _event;
}

void ColliderEventComponent::RemoveEvent()
{	
	// ���g��ID���L�[�Ƃ��āA�n���ꂽ�C�x���g���폜
	auto it = functions_.find(id_);
	if (it != functions_.end())
	{
		functions_.erase(it);
	}
	else
	{
	}
}
