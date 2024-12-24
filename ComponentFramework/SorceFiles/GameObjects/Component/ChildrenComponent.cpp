#include "ChildrenComponent.h"
#include "../GameObject.h"
//-----------------------------------------------------------------
// @brief  �q�I�u�W�F�N�g�̃R���X�g���N�^
//-----------------------------------------------------------------
ChildrenComponent::ChildrenComponent(GameObject* _gameObject, GameObject* _parent, int _updateOrder)
	: Component(_gameObject)
	, parent_(_parent)
{
}
//-----------------------------------------------------------------
// @brief  �q�I�u�W�F�N�g�̃f�X�g���N�^
//-----------------------------------------------------------------
ChildrenComponent::~ChildrenComponent()
{

}
//-----------------------------------------------------------------
// @brief  ����������
//-----------------------------------------------------------------
void ChildrenComponent::Init(void)
{
}
//-----------------------------------------------------------------
// @brief  �X�V����
//-----------------------------------------------------------------
void ChildrenComponent::Update(void)
{
}
//-----------------------------------------------------------------
// @brief  �q�I�u�W�F�N�g�̒ǉ�����
// @param  _child �ǉ�����q�I�u�W�F�N�g
//-----------------------------------------------------------------
void ChildrenComponent::AddChild(GameObject* _child)
{
	children_.emplace_back(_child);
}
//-----------------------------------------------------------------
// @brief  �I������
//-----------------------------------------------------------------
void ChildrenComponent::Uninit(void)
{
	for (auto& child : children_)
	{
		child->Uninit();
	}
}
