#include "ChildrenComponent.h"
#include "../GameObject.h"
//-----------------------------------------------------------------
// @brief  子オブジェクトのコンストラクタ
//-----------------------------------------------------------------
ChildrenComponent::ChildrenComponent(GameObject* _gameObject, GameObject* _parent, int _updateOrder)
	: Component(_gameObject)
	, parent_(_parent)
{
}
//-----------------------------------------------------------------
// @brief  子オブジェクトのデストラクタ
//-----------------------------------------------------------------
ChildrenComponent::~ChildrenComponent()
{

}
//-----------------------------------------------------------------
// @brief  初期化処理
//-----------------------------------------------------------------
void ChildrenComponent::Init(void)
{
}
//-----------------------------------------------------------------
// @brief  更新処理
//-----------------------------------------------------------------
void ChildrenComponent::Update(void)
{
}
//-----------------------------------------------------------------
// @brief  子オブジェクトの追加処理
// @param  _child 追加する子オブジェクト
//-----------------------------------------------------------------
void ChildrenComponent::AddChild(GameObject* _child)
{
	children_.emplace_back(_child);
}
//-----------------------------------------------------------------
// @brief  終了処理
//-----------------------------------------------------------------
void ChildrenComponent::Uninit(void)
{
	for (auto& child : children_)
	{
		child->Uninit();
	}
}
